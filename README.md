# Lab 4 Extending a Factory

In this assignment, you will add a new character to a game in order to practice working with the Factory Design Pattern.

This assignment must be done in groups of two. Although you can work together on the process, each person should make her own monster. Who can come up with a more interesting monster?

## Part 1. Setup.

This assignment can be done using the graphical user interface or using a simple text interface. In the lab, I recommend the GUI. On your own machine, you can install wxWidgets and use the GUI or you can keep things simple and just use the simple UI. 

### wxWidgets

1. If working on your own machine, install wxWidgets. The instructions for Windows are on Moodle. Find instructions for Mac and Linux online. Mac works best if you are using Xcode instead of CodeLite.
2. Copy the HTTPS link for your Git repository on the GitHub website.
3. In CodeLite Git tab, clone the repository into your workspace. Then switch to the new repository.
4. If working on a lab machine, double-check that the permissions do not permit your classmates to access your work.
4. Create a new project. This time, scroll through the templates and expand "GUI" and pick "Executable (wxWidgets enabled)." Browse to the Git repository you cloned. Do not create a separate directory.
5. Right-click on the project name and fix the settings. On Windows, be sure to see the wxWidgets section on Moodle because there is a new piece to this step.
6. Right-click on the "src" folder in the project and add existing files. Select all the .cpp and .h files except main.cpp and simpleinterface.cpp.
7. Delete the main.cpp file from the project.

### Text Interface

2. Copy the HTTPS link for your Git repository on the GitHub website.
3. In CodeLite Git tab, clone the repository into your workspace. Then switch to the new repository.
4. If working on a lab machine, double-check that the permissions do not permit your classmates to access your work.
4. Create a new C++ executable project. Browse to the Git repository you cloned. Do not create a separate directory.
5. Right-click on the project name and fix the settings.
6. Right-click on the "src" folder in the project and add existing files. Select all the .cpp and .h files except main.cpp, wxInterface.h and wxinterface.cpp.
7. Delete the main.cpp file from the project.

### Both Interfaces

If you want to use both interfaces, you will need to create two projects. 

1. Install the first one as directed. 
2. Install the second one, but select the checkbox to create the second project in a separate directory.
3. When you are importing existing files, you will just need to browse up a directory and select the files from there.
4. You are sharing the files between projects, so any change you make in one will affect both projects. 

## Part 2. Testing

After completing this assignment, your program should function just like initially. Run it now and play around with it to get a feel for how it works. 

## Part 3. Create a Monster.

For this project, you will need to make a new file, say `zombie.h` for each of the monsters you make. You should start out by copying an existing monster (`rock.h`, `paper.h` or `scissors.h`). 

You should only make changes in the monster file you created, in monsterfactory.h and in monsterfactory.cpp. If you want to customize the way your monster looks in the GUI, you can also make small changes at the top of wxinterface.cpp.

## Grading

Assignments will only be accepted through GitHub. Be sue to look on GitHub to ensure that your final work is there.

For most of the categoris, you will get 10% for implementing it in one monster, 15% for implementing it two different ways in the two monsters. For example, if the two monsters move the same way, you will get 10%. If they have two different kinds of motion, you will get 15%.

* 10% Good use of git (frequent small commits, clear but brief explanations of the changes)
* 10% Comments (purpose, use, author and date of whole project, purpose of each part of the code, explanations of any complicated code)
* 10% Style (appropriate names for classes, variables, functions, good indentation and use of blank lines, consistent and approrpiate formatting)
* 10% For making two new monsters that may be identical to an existing monster.
* 15% For making the monsters move in a way that is different from the other monsters.
* 15% For changing the `get_appearance()` functions to return something other than the `monster_type`.
* 15% For changing the attack used based on the appearance of the other monster.
* 15% For adding the new monsters to the factory.

Penalties that can be taken off the score you would otherwise get:
* 100% Penalty if you do not use the provided game framework.
* 100% Penalty if you shared work with another group (either giving or getting help) or other innaproriate use of resources.
* 50% Penalty if your program will not compile.
* 20% Penalty if there are any warning messages when your program is compiled with "g++ -Wall -pedantic -std=c++11".
