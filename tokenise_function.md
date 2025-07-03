tokeniseCSV
string csvLine = 'thing,thing2,thing3'  ## the string we are processing

string vector tokens  ## stores the tokens

char separator = ','  ## the character that separates the tokens

int start, end  ## used to delineate the position of the tokens

start = csvLine.find_first_not_of(separator)

do
    end = next 'separator' after start
    if start == csvLine.length or start == end  ## nothing more to find
        break
    if end >= 0  ## we found the separator
        token = csvLine.substr(start, end - start)  ## start, substring length
    else
        token = csvLine.substr(start, csvLine.length - start)  ## end is invalid
    tokens.push_back(token)  ## save the token
    start = end + 1  ## move past this token
while (end > 0)  ## continue loop condition
