

# Explanation

In this video, we will implement the prompt. This will be the last part of our project.
After that, we can do some improvements, but the project itself will be ready to be used.

The read command must return always a lower case string

To command process, I will create a struct to join the command and the handler, but internal.
The same that I did in action manager

To process a command. We use the struct just created. We scan looking for the entered command.

On exit we need to ask: If the user wants to really quit. If the user did some modifications

In remove/update/complete functions. We need to ask the ID.

Next video I will call the prompt to execute and see how many errors will pop up. :)
---------------------------------------------------------------------------------------

In this video let's run the application. First we need to implement all interfaces in appliction layer.

Well, it's quite simple do that. After this we can put the messages, if all things works fine!!!

I hope so. fingers crossed!!!

One thing. I created this project using sat scaffolding.

Here we have a lot of generated code. All application implementation must be in application
file. I mean header and source. There will be the place where we will implement the interfaces.

Prompt already has the interfaces include.

Yeap. Exploded like I imagined. Cool. Real programming!!!! 

It's working. Now we need to put some flowers in the project. Let's start with a menu. 
But first we can mark the diagram.

The prompt we didn't finish yet.

We can do better here. We can avoid to inject display_base in the menu returning the string
to the application. Sounds cool. I guess.

Now we need to find some title to the application.

Well. For this video I think it is enough.
-------------------------------------------------------------------------------------------

The application is running...

But the question is: Is it work? Not sure.

Let's try do some operations and check if really works.

Yeap. I faced a lot of problems here!!! 

Well, this is a part of no one tell us. That suffering. Crazy right?

The application is working now. But there is no life. No color. A dead code.
Let's put some color in this application.

I put the colors here, but just the colors that I'll use here.
I think is a good practice to give colors some meaning.

the green color will be success
the red color will be error
the cyan color will be stylish
the white color will be default


Now to make the life easy. Let's concentrate the display behind a function

We finish the project. But we can keep improving in many ways.

In my case I am a portuguese speaker. It will be nice have some internacionalization resource.

To select which language the program will show its message.

So. Bye

-------------------------------------------------------------------------------------------
So the idea here is to get all the texts in the application and put in one place to
get the message through a tag.

I'll group these texts by error, success, whatever.

The first part is concluded. Now is provide a file using the tags to translate for another language.

-------------------------------------------------------------------------------------------

In this video, I will implement a load file for translate.

In this version will be loaded by argument.

So I need to bring the args from main to inside the application.

For load the file I'll use the sat_file.
The file format will be in JSON. So I'll use sat_json to get the values

These last ones. I don't want to allow to overwrite the ADD, Display ....
So we shift


This bug is because I'm not clearing the buffer before copy a new string.