# Object Oriented Programming
In this repo, you will find two projects demonstrating Object-Oriented Programming (OOP) design in C++.
## LMS
This project involves the design of a Learning Management System (LMS). The main goal of this system is to create university courses and manage their delivery.
### Input Files
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

It is **ensured** that all major_id values used in the files are present in the majors file.
### User Types
Three types of users are implemented: Student, Professor, and Default System User (System Admin). Professor can offer courses, and students can enroll in these courses if they meet the prerequisites. The system admin can add course offerings to the system.
### Input Commands and Output Format
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






## Car wash
In this project, a system for managing a car wash is designed, focusing on tracking the status of employees, cars, and different sections of the car wash. Cars go through several stages of washing as they move through the car wash. Each car proceeds through these stages in sequence, and if there is no available worker for a specific stage, the car waits in line until a worker becomes available. Finally, after completing the last stage, the car exits the car wash.
### Input Files
Some of the information for the program is provided as CSV files. Below is a description of each file.

**Stages.csv**
| Attribute | Description | Datatype |
| --- | --- | --- |
| Id | Each stage's unique Id | Unsigned int |
| Price | Each stage's price | Unsigned int |

**Workers.csv**
| Attribute | Description | Datatype |
| --- | --- | --- |
| Id | Each worker's unique Id | Unsigned int |
| Stage-id | Stage's Id where the worker works | Unsigned int |
| Time-to-finish | Required time for the worker to wash a car | Unsigned int |

Input files are given through command line arguments as shown below:
```console
./CarWashManager.out Stage.csv Workers.csv
```
### Input Commands and Output Format
#### Pass Time

In this command, time advances by the specified amount. A report detailing the changes in the status of the cars during this time is provided.

<ins>Command format</ins>:
```console
pass_time <number_of_time_units>
```
<ins>Output Format</ins>:
```console
<time> Car <ID>: <previous_position> -> <current_position>
```

#### Car Arrival

This command adds a car with specified wash stages to the car wash at the current time. The number of wash stages is not fixed and can vary for different cars. These wash stages are provided as command arguments and are separated by spaces. It is guaranteed that the requested wash stages exist.

<ins>Command format</ins>:
```console
car_arrival <stagesIDs>
```
<ins>Output Format</ins>:
```console
<time> Car <carID>: Arrived -> <position>
```

#### Get Car Status

This command checks the status of a car. The status of the car can be in one of four states:

- `In line`: The car is in the queue for a stage.
- `In service`: The car is currently undergoing a stage.
- `Done`: The car has finished all stages.
- `NOT FOUND`: There is no car with the given ID.

For the `In line` and `In service` states, the name of the respective stage should also be mentioned.

<ins>Command format</ins>:
```console
get_car_status <carID>
```
<ins>Output Format</ins>:
```console
<In line/In service/Done>[: Stage/QueueID]
```
```console
NOT FOUND
```
#### Get Worker Status

This command queries the status of a worker. The status of the worker can be in one of three states:
- `Idle`: The worker is available.
- `Working: <carID>`: The worker is currently working on a car.
- `NOT FOUND`: There is no worker with the given ID.

<ins>Command format</ins>:
```console
get_worker_status <workerID>
```
<ins>Output Format</ins>:
```console
Idle
```
```console
Working: <carID>
```
```console
NOT FOUND
```

**Get Stage Status**

This command provides a report on the status of a stage, including the number of cars that have been washed, the queue of cars waiting for washing, the cars currently being washed, and the revenue generated by the stage. (Note that each car pays the price of the stage after completing it.)

If there is no stage with the given ID, `NOT FOUND` will be printed.

<ins>Command format</ins>:
```console
get_stage_status <stageID>
```
<ins>Output Format</ins>:
```console
Number of washed cars: <Count>
Number of cars in queue: <Count>
Number of cars being washed: <Count>
Income: <Amount>
```
```console
NOT FOUND
```

### How to run
To run the test cases automatically, execute the following bash script:
```console
./judge.sh
```
