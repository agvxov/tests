# Mortal

Gamedev project I started with Emil,
the idea being that surely,
if the scope is small enough,
thats enough to keep us on track.
I did my part,
Emil never finished le input system.
Not that I was particularly motivated either.

This is when we started experimenting with gamejams
and games that hyper-appeal to our interests instead.

---

```
In Peggle, there are only two types of pegs,
 the circle and the block.
Circles are always equal in size.
Blocks have the same thickness,
 but have differing "girth"
 -that is, they bend either up or down-
 which also determines the width of the top and bottom sides.

I understand your concerns of adding more shapes,
 but they are not topical yet.

Peggle also has moving pegs, these usually form some kind of pretty shape,
 e.g, a spinning multi-layered wheel.
While this shall be ommited from prototypes,
 I'm thinking the user should get "motor-blocks" sometimes,
 which have no collision, but a large area of effect inside which
 surounding pegs are moved.

The "fun" aspect of Peggle comes from the visual sattisfaction.
If you look gameplay you will see that it is comperable to our
 hitmarker modding experience.
I believe that it is possible to make it fun while it still resembles battleships,
 however, certain actions will have to be taken.
Hits should be sattisfyingly telegraphed.
Yes, I am suggesting hitmarkers.
They could be positionally overlayed on the shooting player's screen.
Workers exploding into gore is too sattisfying to let slip,
 therefor I suggest when ground units are hit,
 the shooting player gets a slowmo pip into the impact.
This reveal small parts of the other map,
 however it also has the benefitial side effect of
 promoting higher risk block placement,
 that is blocks up in the sky, from where its harder to predict
 what they can effectively protect.
```

---

```
Box2d will own most of our game objects,
 that is everything with physics;
 those being the ball, the walls and all player units.
All of these will contain appropriate user data.
```

---

```
4 walls
Approximate representation:

   |^^^^^^^| walls
   |       |
   |       |
 +------------+
 | |       |  | user viewport
 | |       |  |
 | |_______|  |
 +------------+

The off-screen portion cleanly prevents any jank
 or game ruining dead-lock where we are waiting
 for an infinitly falling ball to settle down.

Something that may help with gameplay is to have
 gradual bouncyness on the side walls.
That is, the lower you hit the wall, the more bouncy it is.
That would be accomplished by defining
 the side walls as multiple adjecent shapes.
```

---

First work split:
+ someone creates the visual compatibility layer so we can see what we are doing
+ the other person figures out a good way to manage input

Then:
+ combinded we figure out how to bend blocks

Then:
+ prettify building (with modifier key, allow snapping to other blocks;
   rotate with mouse wheel)
+ worker logic; research for librandom

Then:
+ make ball collisions destructive and have visual feedback
   (user ball firing not yet implemented!)
+ tetris unit dispenser and money with visual feedback on spending

No further planning until we have something.
