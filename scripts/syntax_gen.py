from jinja2 import Environment, FileSystemLoader
import os

def generate_enum(name, filename):
    with open(filename, 'r') as f:
        kinds = [line.strip() for line in f]

    env = Environment(loader=FileSystemLoader('./'), trim_blocks=True, lstrip_blocks=True)
    template = env.get_template(name + '.templ')
    script_dir = os.path.dirname(__file__)
    parent_dir = os.path.dirname(script_dir)
    output_dir = os.path.join(parent_dir, 'include', 'parser')
    output_path = os.path.join(output_dir, name + '.h')
    with open(output_path, 'w') as f:
        f.write(template.render(kinds=kinds))
        
    template = env.get_template(name + '_impl.templ')
    output_dir = os.path.join(parent_dir, 'src', 'parser')
    output_path = os.path.join(output_dir, name + '.cpp')
    with open(output_path, 'w') as f:
        f.write(template.render(kinds=kinds))

generate_enum('TokenKind', os.path.join(os.path.dirname(__file__), 'TokenKind.txt'))
generate_enum('TriviaKind', os.path.join(os.path.dirname(__file__), 'TriviaKind.txt'))
