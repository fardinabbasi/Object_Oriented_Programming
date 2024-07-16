# Object Oriented Programming
In this repo, you will find two projects demonstrating Object-Oriented Programming (OOP) design in C++.
## LMS

## Car wash
In this project, you will design a system for managing a car wash, focusing on tracking the status of employees, cars, and different sections of the car wash. Cars go through several stages of washing as they move through the car wash. Each car proceeds through these stages in sequence, and if there is no available worker for a specific stage, the car waits in line until a worker becomes available. Finally, after completing the last stage, the car exits the car wash.
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
**Advancing Time**

In this command, time advances by the specified amount. A report detailing the changes in the status of the cars during this time is provided.

Command format:
```console
pass_time <number_of_time_units>
```
Output Format:
```console
<time> Car <ID>: <previous_position> -> <current_position>
```

**Car Arrival**

This command adds a car with specified wash stages to the car wash at the current time. The number of wash stages is not fixed and can vary for different cars. These wash stages are provided as command arguments and are separated by spaces. It is guaranteed that the requested wash stages exist.

Command format:
```console
car_arrival <stagesIDs>
```
Output Format:
```console
<time> Car <carID>: Arrived -> <position>
```

**Get Car Status**

This command checks the status of a car. The status of the car can be in one of four states:

- `In line`: The car is in the queue for a stage.
- `In service`: The car is currently undergoing a stage.
- `Done`: The car has finished all stages.
- `NOT FOUND`: There is no car with the given ID.
For the "In line" and "In service" states, the name of the respective stage should also be mentioned.

Command format:
```console
get_car_status <carID>
```
Output Format:
```console
<In line/In service/Done>[: Stage/QueueID]
```
```console
NOT FOUND
```
**Get Worker Status**

This command queries the status of a worker. The status of the worker can be in one of three states:
- `Idle`: The worker is available.
- `Working: <carID>`: The worker is currently working on a car.
- `NOT FOUND`: There is no worker with the given ID.

Command format:
```console
get_worker_status <workerID>
```
Output Format:
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
