# C-LIBS - Reusable application utility libs for the C language (not C++).

All of this code is meant to be compilable from an C99 compiler. we actively support and GCC 5+ (with -std=c99 -pedantic-errors).  It should also compile under MSVC 2017+ but support may be a bit behind, we do not maintain is as often as we used to.

If a feature of C99 is not available in any supported compiler we do not rely on it within any source code (we'll use macros and platform or OS specific includes to go around it, if possible).

Some of it is high-level, some of it is lower-level, but it's code I've always ended-up re-writing in a variety of projects and languages for many years.

Most of the code here is meant to be 100% platform AND compiler agnostic.  I'm reading a lot of OS manuals and compiler specific flags, and not much C is still so standard across different compilation boundaries.

Defines use different forms in various setups.  platforms like windows and linux have very different includes, often for the exact same functions but with different names.  Even bit depths of various type names may be different.

Interoperability with other languages may be hard to achieve if the types are vaguely defined.  We attempt to solve most of these issues by providing a simple, clean and mostly from scratch approach.  We strive to remove any type of implementation-specific part of C out of the equation.

Every time I try to run code from a tutorial or some guide, or official resources, they fail to compile in one place or another and it is very annoying.  I was tired, so I got to building my own core utilities that run equally well on msvc or GCC, on windows or on linux.  Extra platforms and compilers can be supported, their hooks are pretty obvious.

## License

All the code written by me is licensed with the Apache v2 license.  Any code that is sourced from another project is compatible with the Apache license and will be attributed when author or copyright holder is known.

https://www.apache.org/licenses/LICENSE-2.0


## Not trying to be Popular or trendy

Why do I end up using C instead of C++?  This file will go through a few of the reasons.

I am allergic to most concepts of "best-practices" when they go against logic of simplicity.  Many features in more contemporary C derived languages like C++, Java, C# are very useful, but they are packaged with a quantity of really idiotic language features or syntaxes which mess-up their initial elegance.

I hate being required to chose a technology solely because "everyone is doing it".  I'd rather think on my own, solve the problem at hand and move on.  I've got more than 30 years of programming experience and I've learned and used at least 20 different languages in my life.  Something in C is so elegant its hard to put a finger on it.  It's probably why most of the currently dominant languages are just derivatives of its clean syntax.

Today, C is still the most portable language, bar none.  A C compiler runs on ALL platforms, you can even compile C code for the web.

Please don't comment my code by saying its not compliant to this principle or that best-practice.  I really don't care.  Run the unit tests, and if anything doesn't obey to the specs, then complain.  Hell, contribute with more tests and prove me that something is buggy, I'll be happy to fix it.


### Syntax is not a replacement for reason

A lot of newer features in languages have always been available in plain C with core language features.  They just required understanding and a bit more code or funky pointer notations.

If we look at many "modern" versions of C-derived languages, they are barely readable. I mean, actually reading the code is taxing for the brain.  There is sooo much syntax in the way of clear understanding, that it becomes extremely tiresome work.  

Also things like Generics, while useful, to reduce some amount of coding also leads to massive abuse.  Often simple macro with one or two well documented naming patterns do the same thing. But being forced to work through it will reduce the abuse.

With all this being said, if a feature of compilation is not directly available via C, then there is nothing wrong by using a bit of C++ in the project, but don't use any Classes, and be sure your function names are not C++ decorated in compiled objects.  And NEVER throw Exceptions.


### Break up and make up.

Code reduction Cleanup, really really really pays off in the long run

Ever done cleanup on a 20k source file or twenty 2k files with no comments... would you rather have done it on a single, documented 5k file?

There will be breaking changes, often. Sorry.  No one is forcing you to update.  If we constantly keep the cruft to creep and no cleanup is done when we realize it, it creates a state of code which is tragically harder and harder to cleanup.

Many little changes are MUCH easier to apply in series than complete rewrites which force you to also rewrite.

This is often an exit strategy for users of a library.  They will stay up to a version and never upgrade... just look at how screwed up python is with its v2 and v3 situation.


### No Object-Oriented Programing... 

I am against most top to bottom OOP languages.  With my 35 years of programming experience, I can say they simply offset the maintenance complexity of large codebases and shift the curve to being even worse at some point.  Its like ignoring the cliff, instead of planning for it.  

The cascade of changes required to fix some core class throughout a large codebase is like an avalanche.  question: is it really less dangerous to ski in an avalanche than jumping off a cliff with a parachute... not really.

Don't forget that structures are object classes.  They just rely on you to be organised... and yes that is hard.

I'm not against OOP principles, just hiding behind "_advanced_" OOP syntax of C++ (and downright comma-inducing Objective-C) which is quite abusive. Many OOP codebases don't even follow core paradigm principles which make them even more dangerous, because you expect the classes to be designed properly.  An example is the case where some of the state logic of a class are actually implicitely managed by another object.  If you look around there are some serious thesis on why the OOP paradigm doesn't properly solve the complexity or state management problem, in real-world applications.


### Get shit done

Being a hacker used to mean something positive, sooo much different than today, it's been warped.  It's time this became a quality again.  Hackers are all about being smart, thinking out of the box... 

basically... Getting shit done.

Less lines, simpler more consistent syntax and yes, expectations for people to RTFM.

You'd be amazed at how many fledgling programmers don't even learn how to do the most basic stuff like a reverse loop.  Yes, It's often been my ONLY technical question in hiring, and SOME GET IT WRONG !?!?!  (I admit, others have tried to impress me with a lamba function in haskel, hired ;-)

I am of the school of thought that you should actually learn how, when & why to do things.  

Yes, it's harder and longer, BUT then you become better at doing them.  Artists and tradesmen understand this, programmers should to.  

There is no alternative to being skilled.  Smart people understand this.


### Test, test, test

The project will be ramping up with a proper test suite.  I just haven't chosen how to approach it yet, there are so many ways to do it.

My unit tests are currently still not released, but it will come.



# Repository posting rules

Any Git commit MUST be commented and will require one or two tag(s) to be set at the start of the commit message within square brackets 

example :  `[feat] added logging`


The values of the tags is also fixed to one of the following values, always in lowercase. 

* `[new]` : A new thing in the repository, could be a new module, files, section.
* `[feat]` : New or improved feature
* `[fix]` : Bug fix
* `[wip]` : Work in progress. A commit with no promises. An unfinished work.
* `[revert]` : Some form of rollback on code occured.
* `[doc]`  : Documentation
* `[git]`  : Changes done to any Git setup.  Things like `.gitignore` file changes.
* `[maint]` : Code maintenance, usually non-breaking things like commenting, file renaming, etc.
* `[cleanup]` : Code cleanup, possibly compilation breaking.
* `[ver]` : Version changes in the source code.
* `[tests]` : Unit testing changes.




# c-libs Coding Style-Guide

### Source code rules

* OTBS brace style.   https://en.wikipedia.org/wiki/Indentation_style#Variant:_1TBS_(OTBS)

* TAB indents.  (usually with 4 spaces, but that's the point with tabs) 

* ONLY single line comments ex : ` // a single line comment `

* Comment lines using dash, NOT star  ex :  

```
//-----------------------
// comment within lines
//-----------------------
```

* NO TAB characters WITHIN COMMENTS

* We use a standardized function header template.  Just look at the code, you just need to copy/paste an example from the source.

* No systematic blank lines between source lines.  Only add blank lines to separate logically grouped code, so its easy to understand when there is a group.

* Restrained use of inline comments.

* Lowercase for all arguments and local variables, use underscores.

* `bool` returning functions should use `_is_` in their name if possible. ex : `is_odd()`
	
* CamelCase struct Names ex : `struct MyStruct {...}`

* typedefs for all structs set to the same Name as the struct. ex :  
`typedef struct MyStruct {...} MyStruct;`  Note: NEVER add * to the typedef.

* lowercase prefix for any identifier ex : `struct pfx_MyStruct {...}`

* Uppercase CONSTANTS and MACROS, also for prefix, which is an exception to the previous rule ex : `PFX_MACRO(x)`

* Multi-line arguments with comment descriptions ex : 
```
int MyFunc(
	int x, // horizontal coordinate
	int y  // vertical coordinate
){
	...
	return z;
}
```


_**I will accept NO merge requests with:**_
* Space-indented code
* Block comments.  i.e.   /* */
* systematic use of inline comments.
* use of CamelCase in anything else than a structure name


### Document the WHY, WHEN, HOW, and WHERE

Don't document the _**what**_ ... we already can see it, its the code we're reading.

**WHY** is this function important or different.  Why did we add it.

**HOW** does this function fit in with the rest. You know, that interdependent feature of this and another function.

**WHEN** is this function required or when was it added and what was the cause for this change.

**WHERE** is the other code which uses this.  Where did you get the idea,  where's the reference for the algorithm you're implementing or the problem you're trying to solve.  A Wikipedia link give A LOT of context to a function or file header.

Finally, do document the **WHAT** ... what isn't obvious, because if good code is self descriptive, good comments are self serving.  

In a year's time You'll be happy you won't have to browse and re-read your code for an hour (or a day) to remember why you did this, where it came from, how it may break, when its needed and what the hell you where thinking about not commenting it.  ;-)



### source code project complexity

Everytime I see a project implemented in C++ or some other OOP language I marvel at the line count and the project's file complexity.  I've cut source code by 4x (yes 4 files become one) by just replacing the same logic in simple and clean flow of C code, throwing away all the C++ overhead.

A lot of the "best practices" in many projects I've seen had little to do with quality of code, they where essentially a by-product of managing a large number of bad programmers and limiting their ability to do dumb things... Give an idiot any task and he will still find a way to fuck it up.  To their defense, most clueless programmers are encouraged to stay this way by their management, instead of going in depth and give them the chance to learn, grow and understand what the hell they are using and doing.


### No exceptions

I am also of the opinion (and I am not alone) that the concept of a stack unwinding long jump, a.k.a. an exception, is a feature with so many incidious bug-related side-effects that they are dangerous and quite hard to do right.  

Recent OOP compilers are much better at cleanup... the problems are logic-related.  if any function, 20 levels up in your stack can throw an exception, how do you prepare for the eventuality.  In Fact you can't.  You must either implement exceptions for every line of code or expect someone else up the chain will do it. 

How can a function up the chain realistically deal with all the possible errors all the dependent code tree will throw.  It can't, so it will usually implement some sort of global error trap which can't actually deal with none of them, and hope some form of recovery is possible and either Halt the application or go back to an event wait loop, with some of the application in an undetermined state.

This is exacerbated in system code, which is full of dynamic resource management.  Also in many projects, you end up having to add a lot of `try ... catch` code juste to be sure you properly unwind and follow some clean-up logic... so then where is the advantage?  End result is quite ugly and redundant, and again.. lots lots and lots more lines of code.


### Build APIs then use them

If you are able to describe a problem into a set of features and functionality, then you can create a set of functions to deal with it.  Hey, that sounds like OOP no?  yes and no.  Building a class doesn't mean you've actually tought about your problem and how to solve it using a smart set of properties and orthogonal functionality.  It just means you're hidding it in a theoretical black box.  but it can still be built using a list of nasty one-use functions.

Design your systems so they can be shared in multiple places, maybe simplifying the dataset so it can be re-used.  Three simple systems which collaborate well are in fact 8 different single use, purpose-built designs.  The larger the system, the more this theory scales.  Its an exponential affair.


### Code convergence points

Your code should never leave decision trees partially resolved for later lines to finish up.

Design your flow so it looks like a series of funnels end to end.  If there are 10 steps with 10 decisions each, deal with all decisions at each step entirely before handing over the process to the next step.

Never leave a variable of the first step free to act in a later stage. you will inevitably forget about it and you'll enter the strange world of intra-function side-effects.

When your code tends to have these dangling variables which are used in several stages, its a clear sign that your stages, your variables or your arguments are not properly sorted out.  Maybe you should create an intermediate value which is a reflexion of a set of the decisions of the first stage which will affect the second in one way.

maybe you have 4 variables which affect HOW you processed the first stage, if you need to remember what occured, NEVER reuse these individual variables to try and decide in a later stage how the data was changed. Instead, create a new value which represents a SINGLE list of different possible combined states and ONLY switch on this single value.

This allows your logic to be EXTREMELY clear.  In one stage you deal with `x, y, z, i`, in the other stage you reflect ONLY on ` mode` if any changes to your first stage would affect how `mode` is processed, it probably still doesn't change the mode.  But if you are still using any of the original variables, you'd ALSO have to adjust their use later, which will _**INEVITABLY BE FORGOTTEN**_ .  If something completly new occurs, you may just need to add a new possible value to  `mode` and add a new `case:` to your `switch(mode)` .  That's a LOT easier to follow and maintain.