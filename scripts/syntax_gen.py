from jinja2 import Environment, FileSystemLoader
from pathlib import Path
import math
import yaml

# 获取项目的根目录
ROOT_DIR = Path(__file__).parent.parent

def load_yaml(file_name):
    file_path = ROOT_DIR / 'scripts' / file_name
    with open(file_path, 'r', encoding='utf-8') as file:
        return yaml.safe_load(file)

def render_template(template_name, output_path, context):
    env = Environment(loader=FileSystemLoader(ROOT_DIR / 'scripts'), trim_blocks=True, lstrip_blocks=True)
    template = env.get_template(template_name)
    output_path.write_text(template.render(context), encoding='utf8')

def generate_token(kind_name):
    token_file = ROOT_DIR / 'scripts' / f'{kind_name}.txt'
    with open(token_file, 'r', encoding='utf8') as f:
        kinds = [line.strip().split() for line in f]
        max_length = math.ceil(max(len(kind[0]) for kind in kinds) / 4) * 4

    context = {'kinds': kinds, 'max_length': max_length}
    render_template(f'{kind_name}.templ', ROOT_DIR / 'include' / 'parser' / f'{kind_name}.h', context)
    render_template(f'{kind_name}_impl.templ', ROOT_DIR / 'src' / 'parser' / f'{kind_name}.cpp', context)

def generate_syntax():
    yaml_data = load_yaml('syntax.yaml')
    context = {'data': yaml_data}
    render_template('SyntaxKind.templ', ROOT_DIR / 'include' / 'parser' / 'SyntaxKind.h', context)
    render_template('Syntax.templ', ROOT_DIR / 'include' / 'parser' / 'Syntax.h', context)
    render_template('Syntax_impl.templ', ROOT_DIR / 'src' / 'parser' / 'Syntax.cpp', context)

if __name__ == "__main__":
    generate_token('TokenKind')
    generate_token('TriviaKind')
    generate_syntax()
