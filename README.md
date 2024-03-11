Municipal Election Management Application
Welcome to the Municipal Election Management Application! This application is designed to facilitate various aspects of municipal elections, including user management, vote management, claim management, election management, vote desk management, and observer management. Written in C using the GTK+ framework with Glade, this application provides a user-friendly interface for efficiently managing election-related tasks.

Features
User Management: Administrators can manage user accounts, including adding, editing, and removing users.
Vote Management: Facilitates the process of casting and recording votes securely.
Reclamation/Claim Management: Allows observers to submit claims or complaints regarding the election process.
Election Management: Enables administrators to oversee and manage various aspects of the election process.
Vote Desk Management: Provides tools for managing voting desks and ensuring smooth operations.
Observer/Viewer Management: Allows for the management and oversight of observers participating in the election process.
Installation
If you encounter any issues with installing the required dependencies, you have two options:

Docker Installation: Utilize the provided Dockerfile in the source code to create a Docker image containing the necessary dependencies. Alternatively, you can directly download the Docker image from the provided DockerHub link.

Manual Installation: Follow the manual installation steps to ensure all dependencies are properly installed on your system.

Usage
To connect to the appropriate space within the application, follow these instructions:

Execute the program from the "src" directory.
User data is stored in the text file "ajt_ut.txt" located in the "src" directory.
Access Permissions:

Administrator: Access to user management, election management, and vote desk management.
Voter: Access to voter list management and voting space.
Vote Desk Agent: Access to observer management.
Observer: Access to claim management.
In the voting space:

If a voter does not select any option in the electoral list table, their vote will be counted as a blank vote.
Otherwise, the voter can vote by selecting a single list.
