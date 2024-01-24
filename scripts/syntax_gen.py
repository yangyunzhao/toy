from jinja2 import Environment, FileSystemLoader
from pathlib import Path
import os
import math
import yaml
# =============================================================================
# 词法分析器相关逻辑
def generate_token(name, filename):
    with open(filename, 'r', encoding='utf8') as f:
        kinds = [line.strip().split() for line in f]
        max_length = max(len(kind[0]) for kind in kinds)
        max_length = math.ceil(max_length / 4) * 4

    env = Environment(loader=FileSystemLoader('./'), trim_blocks=True, lstrip_blocks=True)
    template = env.get_template(name + '.templ')
    script_dir = os.path.dirname(__file__)
    parent_dir = os.path.dirname(script_dir)
    output_dir = os.path.join(parent_dir, 'include', 'parser')
    output_path = os.path.join(output_dir, name + '.h')
    with open(output_path, 'w', encoding='utf8') as f:
        f.write(template.render(kinds=kinds, max_length=max_length))
        
    template = env.get_template(name + '_impl.templ')
    output_dir = os.path.join(parent_dir, 'src', 'parser')
    output_path = os.path.join(output_dir, name + '.cpp')
    with open(output_path, 'w', encoding='utf8') as f:
        f.write(template.render(kinds=kinds, max_length=max_length))

generate_token('TokenKind', os.path.join(os.path.dirname(__file__), 'TokenKind.txt'))
generate_token('TriviaKind', os.path.join(os.path.dirname(__file__), 'TriviaKind.txt'))
# =============================================================================
# 语法分析器相关逻辑
def load_yaml(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        return yaml.safe_load(file)

def generate_syntax():
    yaml_data = load_yaml(os.path.join(os.path.dirname(__file__), 'syntax.yaml'))
    env = Environment(loader=FileSystemLoader('./'), trim_blocks=True, lstrip_blocks=True)
    script_dir = os.path.dirname(__file__)
    parent_dir = os.path.dirname(script_dir)
    # =============================================================================
    # SyntaxKind.h
    output_dir = os.path.join(parent_dir, 'include', 'parser')
    output_path = os.path.join(output_dir, 'SyntaxKind.h')
    template = env.get_template('SyntaxKind.templ')
    with open(output_path, 'w', encoding='utf8') as file:
        file.write(template.render(data=yaml_data))
    # =============================================================================
    # Syntax.h
    output_dir = os.path.join(parent_dir, 'include', 'parser')
    output_path = os.path.join(output_dir, 'Syntax.h')
    template = env.get_template('Syntax.templ')
    with open(output_path, 'w', encoding='utf8') as file:
        file.write(template.render(data=yaml_data))
    # =============================================================================
    # Syntax.cpp
    output_dir = os.path.join(parent_dir, 'src', 'parser')
    output_path = os.path.join(output_dir, 'Syntax.cpp')
    template = env.get_template('Syntax_impl.templ')
    with open(output_path, 'w', encoding='utf8') as file:
        file.write(template.render(data=yaml_data))

generate_syntax()
