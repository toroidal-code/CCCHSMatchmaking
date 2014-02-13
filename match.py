import argparse
import textwrap

"""
Computer Matchmaking
CCC Technology Club (1997-2008)
Original program by Mark Marano
Revisions by George Burri
Re-written by Katherine Whitlock
Refer to the Readme for instructions
"""

db_siz = 600
an_siz = 400

db_rec = None

class Student:
    """A simple representation of a student"""
    def __init__(self, arg):
        super(Student, self).__init__()
        self.arg = arg

class Answer(object):
    """docstring for Answer"""
    def __init__(self, arg):
        super(Answer, self).__init__()
        self.arg = arg
        
        
def main():
    parser = argparse.ArgumentParser(description="The CCCHS Valentine's day matchmaking program")
    parser.add_argument('records', type=str, nargs=1, help="The list of students' info")
    parser.add_argument('outfile', type=str, nargs=1, help="The file to output to")
    parser.add_argument('template', type=str, nargs=1, help="The file to use as a template")
    args = parser.parse_args()
    print(args)

if __name__ == '__main__':
    main()