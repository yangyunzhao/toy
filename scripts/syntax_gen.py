from jinja2 import Environment, FileSystemLoader
import os
import math

def generate_enum(name, filename):
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

generate_enum('TokenKind', os.path.join(os.path.dirname(__file__), 'TokenKind.txt'))
generate_enum('TriviaKind', os.path.join(os.path.dirname(__file__), 'TriviaKind.txt'))