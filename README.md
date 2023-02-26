# Data_Structures_and_Algorithms
Throughout this course several data structures were introduced. Mainly, vectors, arrays, linked lists, hash tables, and binary search trees. The main goal was to learn each data structure and decide which structure would be best to solve the problem presented in the projects. The problem presented was to create software for a ficticious university that reads a csv file and stores the information into a data structure. Each line of the csv file will contain a course number, course name, and none to many prerequisites. I approached this problem by first deciding which data structures made the most sense in this situation. The hash table structure was immediately eliminated as I felt using a hash table to sort and store objects by a string variable was not very practical. The vector was eliminated next as a requirement of this project was to print all course objects in alphanumeric order by the course number. Using a vector would require the implementation of a sorting algorithm on the back end which would effect runtime. Therefore, I decided on the binary search tree structure since it sorts upon insertion. After this was decided all that was left was to create the necessary funtions to implement this data structure. This presented several challenges in regards to reading the csv file. Implementing a parser was challenging but I referred to several templates for csv parsers to overcome this challenge. I also faced a challenge debugging the loadCourses() function. I reached out to my instructor for feedback and it gave me insight into where I was going wrong. It turns out I was attempting to parse the file two different ways simulataneously causing a bug. Once I understood that issue, I stuck to a single way to parse the data and the program functioned properly. This project further reinforced the idea of incremental development in my approach to software development. This project showed that it is very important to test each piece of code as you go to make debugging easier.
