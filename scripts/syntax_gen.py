def generate_enum(name, filename):
    with open(filename, 'r') as f:
        kinds = [line.strip() for line in f]

    with open(name + '.h', 'w') as f:
        f.write('enum class ' + name + ' {\n')
        for kind in kinds:
            f.write('    ' + kind + ',\n')
        f.write('};\n')

generate_enum('TokenKind', 'tokenkinds.txt')
generate_enum('TriviaKind', 'triviakinds.txt')