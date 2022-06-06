import re
from queue import LifoQueue as LiFo

camel_split = re.compile(r'[A-Z](?:[a-z]+|[A-Z]*(?=[A-Z]|$))')


def camel_case_split(string: str, first_lower=True):
    if first_lower:
        string = string[0].capitalize() + string[1:]
    return re.findall(camel_split, string)


def title_case_merge(segments) -> str:
    return ''.join(segments)


def lower_underscore_merger(segments: list[str]) -> str:
    segments = [index.lower() for index in segments]
    return '_'.join(segments)


def struct_definition(string: str):
    return title_case_merge(camel_case_split(string))


def struct_member_var(string: str):
    return lower_underscore_merger(camel_case_split(string))


# url = args['url']
path = r"C:/Users/treys/OneDrive/Downloads/cldr/41.0/common/main"
locale_full = r'en_US'
language = 'en'  # Get the language from the first couple letters before the underscore in the locale name


def indent_len(string: str):
    return len(string) - len(string.lstrip())


struct_data = LiFo()


lines = open(f'{path}/{language}.xml', 'r', encoding='utf-8').readlines()  # Create the list of all lines in the file
skip_lines = 0  # This will be what line the comment block ends on, so it can be skipped
while '-->' not in lines[skip_lines]:
    skip_lines += 1  # Find the end of the comment block which is marked by --> NOTE: The valid data starts on the line after the comment block
for line_num in range(skip_lines + 1, len(lines)):  # Iterate through all lines from the end of the comment block to the last line
    if '</' not in lines[line_num] and '/>' not in lines[line_num]:  # Make sure that the line being parsed is not a termination tag (or a tag without a terminator which ends with />)
        tag = re.findall(r'(?<=<).+?(?=[ >])', lines[line_num])[0]  # Parse the tag which resides between < and > for standard tag [eg. <date>] and < and (space) for a tag with attributes [eg. <date type="wide">]
        indent = indent_len(lines[line_num + 1])  # Get how indented the nested entry is, this means that the XML file has to be indented in accordance to the hierarchy to parse correctly
        end_line_num = line_num  # This will be the line that the termination tag is on [eg. if the tag <date> is on line 20 then this will equal whatever line </date> is on such as 100]
        while re.findall(r'(?<=<).+?(?=[ >])', lines[end_line_num])[0] != f'/{tag}':  # Keep going through lines until something matching </{tag}> is found
            end_line_num += 1

        struct_string = 'struct ' + struct_definition(tag) + ' {\n'  # This is the struct definition

        for check_num in range(line_num, end_line_num):  # Next all the member variable names need to be found, and they will all be found between the tag line number and end tag line number found above
            if '</' not in lines[check_num] and indent_len(lines[check_num]) == indent:  # Check that line being checked is not an end tag and that it resides at the index indent number required
                tag = re.findall(r'(?<=<).+?(?=[> ])', lines[check_num])[0]  # Next extract the tag that meets the above requirements as it will be a member variable
                if r'="' in lines[check_num]:  # It has an attribute like type="wide"
                    attribute = re.findall(r'(?<=").+?(?=")', lines[check_num])[0]  # Parse out the attribute it contains as it will serve as the member variable's name
                    struct_string += '\t' + struct_definition(tag) + ' ' + struct_member_var(attribute) + ';\n'
                else:  # If it does not have an attribute, then it is just a tag and can simply be added
                    struct_string += '\t' + struct_definition(tag) + ' ' + struct_member_var(tag) + ';\n'
            elif indent_len(lines[check_num]) == indent:  # This case is for 'variables' which are entries without any nested tags eg. <month type="1">Jan</month>
                try:
                    # struct_string += '\t' + re.findall(r'(?<=>).+?(?=<)', lines[check_num])[0] + ';\n'  # Extract the value to use as a placeholder (could also use key by replacing the > < with " ")
                    None
                except IndexError:  # If there is a problem, just keep going, this is more for manual assistance than a requirement
                    continue
        struct_string += '};\n'  # By the time this is reached, all members variables have been found and added

        struct_data.put(struct_string)

temp_list = []
while not struct_data.empty():
    temp_list.append(struct_data.get())

final_structs = list(dict.fromkeys(temp_list))

for each in final_structs:
    print(each)