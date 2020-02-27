# OS Basics

### What Is An Operating System
 
The operating system is perhaps the most important software on your computer or mobile device. In this article, I am going to describe how the operating system functions both as a resource manager and an extended machine.

The OS as an extended machine is a less common description but indeed it is. The OS provides an abstraction over the hardware and provides a more pleasant interface to program against through system calls. Think about when you want to create a new file, you barely have to worry about the mechanics of the disk and that is because the OS does an excellent job keeping things simple for you through the _sys_write_ **system call**.

System Calls are like an object’s public methods. You can think of them as the OS’ public methods that allow you to change the state of the OS. The OS provides system calls that developers can then use to do things like creating a new process or file.

The more common description of an OS is as a resource manager. Co-ordinating interaction with IO devices and how long a program runs. Say you have programs A and B that want to write to the same file, your intent is that A should write then B should follow since A was the first program to begin writing anyway. The file here is the resource. What the OS will do is put a lock on the file while A is writing to it and allow B to manipulate the file only when the lock is open.

As you can tell from above that the OS is an essential piece of software.
