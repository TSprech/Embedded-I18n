import re
from queue import LifoQueue as lifo
# import queue

camel_split = re.compile(r'[A-Z](?:[a-z]+|[A-Z]*(?=[A-Z]|$))')


def camel_case_split(string: str, first_lower = True):
    if first_lower:
        string = string[0].capitalize() + string[1:]
    return re.findall(camel_split, string)


def title_case_merge(segments) -> str:
    return ''.join(segments)


def lower_underscore_merger(segments: list[str]) -> str:
    segments = [index.lower() for index in segments]
    return '_'.join(segments)


def find_locale_point(data, *argv):
    """
    Finds locale data inside a CLDR XML file.
    :param data: A list of file objects in decreasing specificity | eg. [en_US, en].
    :param argv: The series of tags and attributes which specify the location of the desired data | eg. 'delimiters', 'quotationStart'.
    :returns: The data found at the specified tag/attribute path.
    """
    for file in data:
        try:  # Try to find the data in more specific files and move to more general files in accordance with the search_order list
            result = file  # Result will be the value found at the specified XML category
            for arg in argv:
                if arg[0] == '@':  # A string starting with an @ sign means that it is an attribute, so a search must be done to see where it is
                    key, attr = arg.split('=')
                    if isinstance(result, list):
                        result = next((item for item in result if item[key] == attr), None)  # Find the dictionary which contains the attribute value
                    # If it is already a dict, do nothing, as there is no need to iterate through multiple lists to see which one has the right attribute
                else:
                    try:
                        result = result[arg]  # If it is not an attribute, then it is likely a dictionary, so it can just be indexed into
                    except TypeError:
                        raise KeyError  # If however it was not a dictionary, then there is some other issue (most likely not a locale specific entry for it) so skip to the next search level
            return result  # If it successfully completed the above for loop, then the data was found and it can be returned
        except KeyError:  # This most likely means that the locale data is not specified in the specific XML file, so proceed to the general XML file
            continue


def write_locale_data(data: str, file):
    if file is None:
        print(data)
    else:
        file.write(data + '\n')


# url = args['url']
path = r"C:/Users/treys/OneDrive/Downloads/cldr/41.0/common/main"
locale_full = r'en_US'
language = 'en_MINE'  # Get the language from the first couple letters before the underscore in the locale name

with open(f'{path}/{language}.xml', 'r', encoding='utf-8') as general_locale:
    struct_data = lifo()  # A lifo is used because the data is presented hierarchically, however we generate structs from the most specific to most broad to avoid having to forward declare all of them
    for str_line in general_locale.readlines():
        # if '<' in str_line and '>' in str_line:
        if str_line.count('<') == 1 and str_line.count('>') == 1:  # Check if the str_line is a tag
            directives = re.findall(r"(?<=<).+?(?=>)", str_line)[0]  # Extract everything between the < and >
            struct_data.put(directives)  # Place the data in the LIFO

    inverted_data = lifo()  # This LIFO will serve to invert the reversal of the first LIFO as the first LIFO is iterated through

    last_data = None  # The more specific (deeper in hierarchy) data tag
    indent = 0
    while not struct_data.empty():  # Go through all the tags
        current_data = struct_data.get()
        if not current_data[0] == '/':  # If the popped data is not a tag termination (eg. </dates>)
            indent -= 2
            # print(' ' * indent + 'struct ' + title_case_merge(camel_case_split(current_data)) + ' {')
            if last_data is not None:  # The first iteration through there is no prior data
                # print(' ' * (indent - 2) + title_case_merge(camel_case_split(last_data)) + ' ' + lower_underscore_merger(camel_case_split(last_data)))
                inverted_data.put(' ' * (indent - 2) + title_case_merge(camel_case_split(last_data)) + ' ' + lower_underscore_merger(camel_case_split(last_data)))  # The last data (the last struct generated) will have a member instance in the parent struct
            inverted_data.put(' ' * indent + 'struct ' + title_case_merge(camel_case_split(current_data)) + ' {')  # Generate the parent struct
        else:
            indent += 2
            # print(' ' * indent + '}')
            inverted_data.put(' ' * indent + '}')  # If it is a tag termination, then close the brace
        last_data = current_data

    # Print out the data
    while not inverted_data.empty():
        print(inverted_data.get())
