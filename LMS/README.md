# LMS
This project involves the design of a Learning Management System (LMS). The main goal of this system is to create university courses and manage their delivery.
## Input Files
Some of the information for the program is provided as CSV files. Below is a description of each file.

**majors.csv**
| Attribute | Description | Datatype |
| --- | --- | --- |
| mid | Major ID | Unsigned int |
| major | Each major's name | String |

**students.csv**
| Attribute | Description | Datatype |
| --- | --- | --- |
| sid | Student ID | Unsigned int |
| name | Each student's name | String |
| major_id | Each student's major | Unsigned int |
| semester | Each student's semester | Unsigned int |
| password | Each student's password | String |

**courses.csv**
| Attribute | Description | Datatype |
| --- | --- | --- |
| cid | Course ID | Unsigned int |
| name | Each course's name | String |
| credit | Each course's credit | Unsigned int |
| prerequisite | Minimum allowed semester to take the course | Unsigned int |
| majors_id | Allowed majors to take the course  | unsigned int |

**teachers.csv**
| Attribute | Description | Datatype |
| --- | --- | --- |
| pid | Professor ID | Unsigned int |
| name | Each professors's name | String |
| major_id | Each Professor's major | Unsigned int |
| position | Each professor's position | String |
| password | Each professor's password | String |

Input files are given through command line arguments as shown below:
```console
./UTms.out majors.csv students.csv courses.csv teachers.csv

```

It is **ensured** that all major_id values used in the files are present in the majors file.
## User Types
Three types of users are implemented: `Student`, `Professor`, and `Default System User (System Admin)`. Professor can offer courses, and students can enroll in these courses if they meet the prerequisites. The system admin can add course offerings to the system.
## Input Commands and Output Format
* The usage of the program is such that the user inputs a command along with the required arguments via the command-line interface into the standard input. For example, to get a list of entity information, the user would enter the `GET` command, and if they want to get specific information about a particular entity, they would enter the entity ID after the command to execute the desired action.

* Note that these arguments, following the `?` in the command, do not need to be in any specific order; that is, the arguments do not have to be entered in the exact order described in the command instructions. Also, for commands without arguments, the `?` symbol is still used.

* Another point regarding commands is that before entering the command, one of the keywords `GET`, `POST`, `DELETE`, or `PUT` must be specified to distinguish the commands. Commands used to retrieve information from the system fall under the `GET` category; `POST` is used to input data, `PUT` is used to update existing information, and `DELETE` is used to remove data.

For each command executed, a response is received from the system. This response may include the information requested from the system.

**Successful Request Response**

If a command entered by the user is executed correctly and completed, this response will be displayed. In some cases, the command itself may have a more detailed output, in which case this response will not be shown.
```console
OK
```
**Empty Response**

If the requested list from the system does not contain any displayable items, this response will be shown to the user.
```console
Empty
```
**Not Found Response**

If the entered command is not found in the list of commands `PUT`, `DELETE`, `POST`, or `GET`, this message will be displayed. Additionally, if the ID does not exist or if a search yields no results in any section, this response will be given.
```console
Not Found
```
**Bad Request Response**

If the first part of the user's input does not match any of the command types `PUT`, `POST`, `GET`, or `DELETE`, this response will be displayed. Additionally, if the command entered lacks sufficient information for execution or if the format of the entered command does not match any of the expected commands (e.g., arguments are not correctly provided or argument values are not as expected), this response will be shown.
```console
Bad Request
```

**Unauthorized Access Response**

If a user enters a command from another user's list of commands, this message will be displayed.
```console
Permission Denied
```

**Error Handling**

The prioritization of error handling in the execution of the program is as follows:

1. First, it is checked whether the command starts with one of the methods `PUT`, `POST`, `GET`, or `DELETE`. If the command does not start with any of these four keywords, a `Bad Request` error is displayed.

2. Next, it is checked whether the entered command exists in the list of commands; for example, the command `GET <existent_non_something>` is not in the program's commands. In this case, a `Not Found` response should be displayed.

3. Then, access permissions are checked for each command. If access is denied, the user encounters a `Permission Denied` error. This error can occur if the user has not logged in or if a user enters commands intended for a different type of user.

4. Finally, specific cases of each command are examined to ensure that only one of the special cases is encountered (multiple errors should not occur here).

### Send Post
<ins>Command format</ins>:
```console
POST post ? title <title> message <message> image <image_address>
```
<ins>Output Format</ins>:
```console
OK
```
```console
Bad Request
```
### Add Profile Photo
<ins>Command format</ins>:
```console
POST profile_photo ? photo <photo_address>
```
<ins>Output Format</ins>:
```console
OK
```
```console
Bad Request
```
### Add Post to Course Channel
<ins>Command format</ins>:
```console
POST course_post ? id <id> title <title> message <message> image <image_address>
```
<ins>Output Format</ins>:
```console
OK
```
```console
Bad Request
```
```console
Not Found
```
```console
Permission Denied
```
### View Course Channel's Posts
<ins>Command format</ins>:
```console
GET course_channel ? id <id>
```
<ins>Output Format</ins>:
```console
<id> <name> <capacity> <professor> <time> <exam_date> <class_number>
<post_id> <author_name> “<title>”
<post_id> <author_name> “<title>” ...
```
```console
OK
```
```console
Bad Request
```
```console
Not Found
```
```console
Permission Denied
```
### View a Post from Course Channel 
<ins>Command format</ins>:
```console
GET course_post ? id <id> post_id <post_id>
```
<ins>Output Format</ins>:
```console
<id> <name> <capacity> <professor> <time> <exam_date>
<class_number>
<post_id> <author_name> “<title>” “<message>”
```
```console
OK
```
```console
Bad Request
```
```console
Not Found
```
```console
Permission Denied
```
### Create a TA Form
<ins>Command format</ins>:
```console
POST ta_form ? course_id <course_id> message ”<message>”
```
<ins>Output Format</ins>:
```console
OK
```
```console
Bad Request
```
```console
Not Found
```
```console
Permission Denied
```
### Close a TA Form
<ins>Command format</ins>:
```console
POST close_ta_form ? id <id>
```
<ins>Output Format</ins>:
```console
We have received <number_of_requests> requests for the teaching assistant position
<first_person_information>:
<second_person_information>:
...
```
```console
Bad Request
```
```console
Not Found
```
### Apply a TA Position
<ins>Command format</ins>:
```console
POST ta_request ? professor_id <professor_id> form_id <form_id>
```
<ins>Output Format</ins>:
```console
OK
```
```console
Bad Request
```
```console
Not Found
```
```console
Permission Denied
```
### Login
<ins>Command format</ins>:
```console
POST login ? id <id> password <password>
```
<ins>Output Format</ins>:
```console
OK
```
```console
Bad Request
```
```console
Not Found
```
```console
Permission Denied
```
### Logout
<ins>Command format</ins>:
```console
POST logout ?
```
<ins>Output Format</ins>:
```console
OK
```
```console
Bad Request
```
```console
Not Found
```
```console
Permission Denied
```
### View Offered Courses
