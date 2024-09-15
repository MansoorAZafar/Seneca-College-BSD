import pickle;
"""
* The Max value that can be received from a Client or Server
"""
MAX_RECV = 4096;

"""
* This function will returned a pickled object
* -> if the data is a file:
*   -> read the file and put the info into a "content" variable
* -> otherwise assign the 'content' to the @data param
* -> return a pickled object of the content
*
* @data   : the information that will be pickled 
* @is_file: defaulting to True, used to determine how to pickle the object
            (for files, we read the all the content and pickle that, thats why
             files have a special process)
"""
def serializeFiles(data, is_file=False):
    if is_file:
        content = None;
        with open(data, "rb") as f:
            content = f.read();
    else:
        content = data;
    try:
        return pickle.dumps(content);
    except Exception as e:
        print(f'could not pickle.dumps(content) {e}')

#gets a 'pickled file obj'
#returns an UNpickled file obj
"""
* This function will return an un-pickled object
*
* @data: The information that will be unpickled
"""
def deserializeFiles(data):
    try:
        return pickle.loads(data);
    except Exception as e:
        print(f'could not pickle.loads(data) {e}');


#Takes in a new_file name and a UNpickled file object
"""
* This function will save an un-pickled object to a file
* -> open the file with binary writing
* -> dump the data into the new file 
*
* Note: We use 'wb' since it's a binary pickled file, meaning we need to write with binary too
*
* @new_file: the file that the information from the data will be saved to
* @data    : the information to be put into a file
"""
def saveToDisk(new_file, data):
    with open(new_file, "wb") as f:
        try:
            pickle.dump(data, f);
        except Exception as e:
            print(f'could not pickle.dump(data, f) into new file {e}')

"""
* Dummy functions that can be sent over from Question 2
"""
def add(x, y):
    return x + y

def multiply(x, y):
    return x * y