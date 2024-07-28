

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

Here we can a lot of generated code. All application implementation must be in application
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