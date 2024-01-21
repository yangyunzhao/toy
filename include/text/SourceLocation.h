/**
 * @file SourceLocation.h
 * @brief 包含了源代码位置相关的结构体和类的头文件。
 * @author yangyunzhao@gmail.com
 */

#pragma once

#include "util/Util.h"
#include <compare>
#include <concepts>
#include <stdint.h>
#include <string>
#include <string_view>
#include <vector>

/**
 * @struct BufferID
 * @brief 表示源代码缓冲区的标识符的结构体。
 * @details 表示从文件加载的源代码、从内存中分配的文本或宏扩展。
 * 每次进行宏扩展时，都会分配一个新的 BufferID 来跟踪扩展位置和原始定义位置。
 * 这对于编译器的错误报告和代码分析等功能非常重要。
 */
struct BufferID {
    /**
     * @brief 默认构造函数，创建一个无效的 BufferID。
     */
    BufferID() = default;

    /**
     * @brief 构造函数，根据给定的值和名称创建 BufferID。
     * @param value BufferID 的值
     * @param name BufferID 的名称
     */
    constexpr BufferID(uint32_t value, std::string_view name)
        : id(value)
        // clang-format off
#ifdef DEBUG
        , name(name)
#endif
        // clang-format on
    {
        (void)name;
    }

    /**
     * @brief 检查 BufferID 是否有效。
     * @return 如果 BufferID 有效，则返回 true；否则返回 false
     */
    [[nodiscard]] bool valid() const {
        return id != 0;
    }

    /**
     * @brief 比较两个 BufferID 是否相等。
     * @param rhs 另一个 BufferID
     * @return 如果两个 BufferID 相等，则返回 true；否则返回 false
     */
    bool operator==(const BufferID& rhs) const {
        return id == rhs.id;
    }

    /**
     * @brief 比较两个 BufferID 的大小关系。
     * @param rhs 另一个 BufferID
     * @return 如果当前 BufferID 小于 rhs，则返回负值；如果当前 BufferID 等于 rhs，则返回 0；如果当前 BufferID 大于 rhs，则返回正值
     */
    std::strong_ordering operator<=>(const BufferID& rhs) const {
        return id <=> rhs.id;
    }

    /**
     * @brief 获取 BufferID 的值。
     * @return BufferID 的值
     */
    constexpr uint32_t getId() const {
        return id;
    }

    /**
     * @brief 将 BufferID 转换为 bool 值。
     * @return 如果 BufferID 有效，则返回 true；否则返回 false
     */
    explicit operator bool() const {
        return valid();
    }

    /**
     * @brief 获取一个占位符 BufferID，其值为 UINT32_MAX，名称为空字符串。
     * @return 占位符 BufferID
     */
    static BufferID getPlaceholder() {
        return BufferID(UINT32_MAX, ""sv);
    }

#ifdef DEBUG
    std::string_view name;
#endif

private:
    uint32_t id = 0; ///< BufferID 的值
};

/**
 * @class SourceLocation
 * @brief 表示源代码中的一个位置（或宏扩展中的位置）的类。
 * @details 如果 SourceLocation 是文件位置，则可以将其解码为文件、行和列信息；
 * 如果 SourceLocation 是宏位置，则可以将其解码为扩展和原始位置。
 * 用于跟踪源代码中的位置，这对于错误报告、警告、代码导航等功能非常重要。
 */
class SourceLocation {
public:
    /**
     * @brief 默认构造函数，创建一个无效的源位置。
     */
    constexpr SourceLocation()
        : bufferID(0), charOffset(0) {
    }

    /**
     * @brief 构造函数，根据给定的缓冲区和字符偏移量创建源位置。
     * @param buffer 源位置所在的缓冲区
     * @param offset 源位置的字符偏移量
     */
    constexpr SourceLocation(BufferID buffer, uint64_t offset)
        :
#ifdef DEBUG
        bufferName(buffer.name)
        ,
#endif
        bufferID(buffer.getId())
        , charOffset(offset) {
    }

    /**
     * @brief 获取源位置所在的缓冲区。
     * @return 源位置所在的缓冲区
     */
    BufferID buffer() const {
#ifdef DEBUG
        return BufferID(bufferID, bufferName);
#else
        return BufferID(bufferID, ""sv);
#endif
    }

    /**
     * @brief 获取源位置的字符偏移量。
     * @return 源位置的字符偏移量
     */
    [[nodiscard]] size_t offset() const {
        return (size_t)charOffset;
    }

    /**
     * @brief 检查源位置是否有效。
     * @return 如果源位置有效，则返回 true；否则返回 false
     */
    [[nodiscard]] bool valid() const {
        return buffer().valid();
    }

    /**
     * @brief 将源位置转换为 bool 值。
     * @return 如果源位置有效，则返回 true；否则返回 false
     */
    explicit operator bool() const {
        return valid();
    }

    /**
     * @brief 计算偏移量为 delta 的源位置。
     * @tparam T 偏移量的类型，必须是整数类型
     * @param delta 偏移量
     * @return 计算后的源位置
     */
    template <std::integral T>
    SourceLocation operator+(T delta) const {
        return SourceLocation(buffer(), size_t((T)charOffset + delta));
    }

    /**
     * @brief 计算偏移量为 delta 的源位置。
     * @tparam T 偏移量的类型，必须是整数类型
     * @param delta 偏移量
     * @return 计算后的源位置
     */
    template <std::integral T>
    SourceLocation operator-(T delta) const {
        return SourceLocation(buffer(), size_t((T)charOffset - delta));
    }

    /**
     * @brief 将源位置的偏移量增加 delta。
     * @tparam T 偏移量的类型，必须是整数类型
     * @param delta 偏移量
     * @return 修改后的源位置的引用
     */
    template <std::integral T>
    SourceLocation& operator+=(T delta) {
        charOffset = size_t((T)charOffset + delta);
        return *this;
    }

    /**
     * @brief 将源位置的偏移量减去 delta。
     * @tparam T 偏移量的类型，必须是整数类型
     * @param delta 偏移量
     * @return 修改后的源位置的引用
     */
    template <std::integral T>
    SourceLocation& operator-=(T delta) {
        charOffset = size_t((T)charOffset - delta);
        return *this;
    }

    /**
     * @brief 计算两个源位置之间的偏移量。
     * @param loc 另一个源位置
     * @return 两个源位置之间的偏移量
     */
    ptrdiff_t operator-(SourceLocation loc) const {
        assert(loc.buffer() == buffer());
        return (ptrdiff_t)charOffset - (ptrdiff_t)loc.charOffset;
    }

    /**
     * @brief 比较两个源位置是否相等。
     * @param rhs 另一个源位置
     * @return 如果两个源位置相等，则返回 true；否则返回 false
     */
    bool operator==(const SourceLocation& rhs) const {
        return bufferID == rhs.bufferID && charOffset == rhs.charOffset;
    }

    /**
     * @brief 比较两个源位置的大小关系。
     * @param rhs 另一个源位置
     * @return 如果当前源位置小于 rhs，则返回负值；如果当前源位置等于 rhs，则返回 0；如果当前源位置大于 rhs，则返回正值
     */
    std::strong_ordering operator<=>(const SourceLocation& rhs) const {
        if (auto cmp = uint32_t(bufferID) <=> uint32_t(rhs.bufferID); cmp != std::strong_ordering::equal)
            return cmp;
        return charOffset <=> rhs.charOffset;
    }

#ifdef DEBUG
    std::string_view bufferName;
#endif

    /**
     * @brief 一个保留的位置，用于表示“没有位置”。
     */
    static const SourceLocation NoLocation;

private:
    uint64_t bufferID : 28;   ///< 保存缓冲区的 ID
    uint64_t charOffset : 36; ///< 保存字符偏移量
};

#ifndef DEBUG
static_assert(sizeof(SourceLocation) == 8); ///< 在非 DEBUG 模式下，确保 SourceLocation 的大小为 8 字节
#endif
