# CUTSCENE MANAGER

I am Alex Campamar, student of the Bachelor’s Degree in Video Games by UPC at CITM. This content is generated for the second year’s subject Project 2, under supervision of lecturer Ricard Pillosu.

## History of cutscenes

The first cutscene of all time was realeased in pac-man. It was a very primitive version of what we can look today, but it's the begginig of what are today cutscenes. This cutscenes didn't have so much narrative importance, but tells a story. You can check it [here](https://www.youtube.com/watch?v=UGQ5sOWuzy8). The same year, space invaders also included cutscenes.

But who really make cutscenes what we know nowadays is Ron Gilber, the designer of Monkey Islad 2 and many other games. He created the term cutscenes and was the first in use it in a similar way that actual games. The first game in wich Ron Gilbert used cutscenes with huge narrative important was Maniac Mansion.


## What's a cutscene?

Cutscenes are a non-interactive sequence in videogames. In many cases, it’s used to explain the story of the game, but it have many uses.

We can difference cutscenes in different types:

### Pre rendered cutscenes
These cutscenes are animated and rendered independent from the game. There are videos played in the game.  Here is an example

Advantages: Higher quality

Disadvantages: Is too heavy and need to be charged, often with a charge screen. That's negative for the player inmersion.

<iframe width="854" height="480" src="https://www.youtube.com/embed/MVbeoSPqRs4" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

### Real Time cutscenes
These cutscenes are rendered with the game engine and the game graphics. It's also known as machinima.

Advantages: Breaks lees the player inmersion, because graphics don't change his quality. Also are fastest to charge and things like player weapons, armors etc adquired in the game can be showed in the cutscene.

Disadvantages: Lower quality, but nowadays the game engines are enough powerful to don't have so much difference with pre rendered cutscenes

<iframe width="854" height="480" src="https://www.youtube.com/embed/q0DAv34i8fQ" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

### Interactive cutscenes

In this cutscenes, the player take the control of the character and do sequences of buttons that appears on the screen. This is also known as quick time event.

Advantages: These cutscenes don't stop gameplay, the player have to do things.

Disadvantages: Players are less focused in what the cutscene is explaining.

<iframe width="854" height="480" src="https://www.youtube.com/embed/nHZy_4WaYeM" frameborder="0" allow="autoplay; encrypted-media" allowfullscreen></iframe>

## How works my cutscene manager?

My cutscene works as a time line. In a xml you can definde as cutscenes as you want, with all actions you want. Every action have a start and end time, and depending on what action is ordered, another things.

```.cpp
<!--cutscene action codes: 0->MoveX 1->MoveY 2->MoveCameraX  3->MoveCameraY-->

<cutscenes>
  <cutscene1>

    <cutscene_action cutscene_action ="0" actor="1" start_time ="0" end_time="500" speed="2"/>
    <cutscene_action cutscene_action ="1" actor="1" start_time ="500" end_time="1000" speed="2"/>
    <cutscene_action cutscene_action ="0" actor="1" start_time ="1000" end_time="1500" speed="-2"/>
    <cutscene_action cutscene_action ="1" actor="1" start_time ="1500" end_time="2000" speed="-2"/>

    <cutscene_action cutscene_action ="1" actor="2" start_time ="0" end_time="200" speed="-2"/>
    <cutscene_action cutscene_action ="0" actor="2" start_time ="200" end_time="700" speed="2"/>
    <cutscene_action cutscene_action ="1" actor="2" start_time ="700" end_time="1200" speed="2"/>
    <cutscene_action cutscene_action ="0" actor="2" start_time ="1200" end_time="1700" speed="-2"/>
    <cutscene_action cutscene_action ="1" actor="2" start_time ="1700" end_time="2000" speed="-2"/> 
    
  </cutscene1>
</cutscenes>
```
Here are only moves, so in xml are defined  start and end time, an actor to move and his speed.

When a cutscene is charged, a timer starts and when one task approach the start time, starts executing.
```.cpp
if (CutsceneActions.front() != nullptr) {

			for (std::list<CutsceneAction*>::iterator it = CutsceneActions.begin(); it != CutsceneActions.end(); it++) {

				if ((*it)->start_time <= Cutscene_timer.Read()) {

					if ((*it)->Execute()) {

						CutsceneActions.remove((*it));
						(*it)->~CutsceneAction();
					}
				}
			}
		}

```
When end time is approached, the function execute (wich contains the order of that action) this function return false and that action is popped from the cutscene actions list.

```.cpp
bool MoveX::Execute()
{
	bool ret = false;

	if (App->cutscene_manager->Cutscene_timer.Read() <= end_time) {
		if (move_speed >= 0) {
			actor->curr_animation = &actor->walk_right;
		}

		else {
			actor->curr_animation = &actor->walk_left;
		}

		actor->position.x += move_speed;
	}

	else {
		ret = true;
	}
	return ret;
}
```

If you want to know more, i've done a handout with some to do's to understand better how it works. 
### [Download it here](https://github.com/Acaree/Cutscene-manager/releases/tag/1.0) 


Behind this, there are also a more extended explain for TO DO'S

### TODO 1: 
Here you only need to take a look the xml, where are defined all cutscene actions we'll charge

### TODO 2:
In the execute method of every Cutscene action we'll define what will do every task and return true when task is finished (end time approached)

### TODO 3:
In this function, we'll receive a cutscene enum and we just need to charge that node from xml (cutscene1 in this case)

### TODO 4:
According with the line commented in the xml, we'll push to the cutscene actions list one action or another. This is determined in cutsceneaction attribute. We'll charge the rest of atributes in the creation of the class.

### TODO 5:
In update we charge cutscene, start timer and change the executing cutscene bool. After that, in ExecuteCutscene method we'll iterate the list of cutscenes actions. We'll call to the execute of the actions wich his start time has passed and delete those actions that return true (that will happen when endtime is approached, do it in todo 2).

## Useful links

https://www.reddit.com/r/gamedev/comments/1x3o9o/how_should_i_go_about_adding_unique_events/

https://www.youtube.com/watch?v=oOhXBcmLq2M

https://www.reddit.com/r/gamedev/comments/1jjxrk/how_do_you_handle_cut_scenes_and_scripting_systems/

https://en.wikipedia.org/wiki/Cutscene

https://gamedev.stackexchange.com/questions/111177/why-not-pre-render-story-parts-in-a-game

https://www.youtube.com/watch?v=u_VAJbQW0Ho

