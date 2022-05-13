import os

def unarchive():
    # Extract archived lines and delete contents
    file = open('bytes', 'rb')
    with file as bytes: lines = bytes.readlines()
    open('bytes', 'wb').close()

    file_name = ''
    data_line = 0
    for i, line in enumerate(lines):
        if i == data_line: 
            try: file_name.close()
            except: pass
            str(line)
            file_name = line.split()[0]
            lines_to_read = int(line.split()[1])
            data_line += lines_to_read + 1
            
            open(file_name, 'x')
            file = open(file_name, 'wb')
        else: file.write(line)
    
def archive(file):
    # Read files contents
    file_contents = []
    file_contents_lines = 0
    file = open(file, "rb")
    with file as f: lines = f.readlines()
    for line in lines:
        file_contents.append(bytearray(line))
        file_contents_lines += 1

    # Archive contents and properties
    bytes = open("bytes", "wb")
    bytes.write(file.name.encode()) 
    bytes.write((' ' + str(file_contents_lines) + '\n').encode())
    for content in file_contents:
        bytes.write(content)
    bytes.close()
    os.remove(file.name)

archive('img.png')
unarchive()