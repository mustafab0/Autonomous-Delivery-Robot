# Autonomous Delivery Robot
An autonomous delivery robot that navigates in a grid-map using Djikstra's algorithm for path planning. The path planning algorithm runs on a Raspberry Pi and the path information is sent over UART serial interface to a multi-core microcontroller that moves the robot accordingly.

The path planning occurs based on a real-time object detection and line following running on separate cores on the micro-controller using an ultrasonic and infrared sensor array respectively.

The system also includes a robot perception system that runs on the raspberry Pi to detect an enemy/friendly and sends information over the Serial Comm.

![Delivery Robot](images/bot.png)

The path planning and perception system runs on a raspberry pi and instructions are sent over UART communication to a multi-core microcontroller, that performs line following, object detection and motion of the robot.

Since a major part of the project was to use two devices together we decided to break our solution into two halves and assign each device to perform a specific task. The following is how we broke down the solution.

![Project Breakdown](images/workflow.png)
