# JET-FIGHTER-PLANE

# DEVELOPER
		ADITYA JAIN PANSARI
# Running the game
* To run the game enter these command in the directory of the game:
		run	./graphics_asgn1 in directory build 
		
# Rules
* You can use missiles/bombs to kill enemies (cannons and parachutes).
* A powerup in the form of Green parachute if taken provides health regeneration.
* A powerup in the form of Brown parachute if taken provides fuel regenration.

# Point Scheme
* Destroy enemy Cannons -> 100
* Destroy Parachutes (using Missiles) -> 50
* Destroy Parachutes (hit with Plane) -> 10
* Pass through Fire Rings -> 200

# Health Can Be Reduced by
* Going Under-Water -> -0.1
* Get hit by Cannon Fire_Balls -> -1
* Get hit by Parachute -> -1
* Go near Volcanoes (NO-FLYING-ZONE) -> -5

# Health Can Be Increased by
* Health regenerates automatically when inside the green parachutes.

# Fuel Can Be Increased by
* Fuel regenerates automatically when inside the grey parachutes.

# Player Can Be Killed by
* Health goes ZERO
* Fuel Tank goes EMPTY

# Camera Views
* Cockpit View (Pilot's Eye)
  * This is a view from inside the plane’s cockpit which is from inside the front wind-shield. Only a part of the world in front is visible. In other words, in this view, we see what the pilot sees, as if we were the pilot.
  * It is easy to aim a Missile using this view.
  <img src='./images/cockpit1.png' width=364px alt="Cockpit_View" />
  <img src='./images/cockpit2.png' width=364px alt="Cockpit_View" />
  <!--[Cockpit_View](./images/cockpit1.png?raw=true)-->
  <!--[Cockpit_View](./images/cockpit2.png?raw=true)-->
* Top View (Bird's Eye)
  * This is a top-down view, as if we were looking vertically downwards from a position in the sky. This gives a clear picture of the path.
  * It is easy to aim a Drop-Bomb using this view.
  <!--[Top_View](./images/birds_eye_view_top_view.png?raw=true)-->
  <img src='./images/birds_eye_view_top_view.png' width=364px alt="Top_View" />
* Tower View
  * Here, the camera is sitting on a tower, to the side of the plane of playing, observing it at an angle.
  <!--[Tower_View](./images/tower_view1.png?raw=true)-->
  <img src='./images/tower_view1.png' width=364px alt="Tower_View" />
  <img src='./images/tower_view2.png' width=364px alt="Tower_View" />
  <!--[Tower_View](./images/tower_view2.png?raw=true)-->
* Follow-cam View
  * This is a view of the plane and the region in front of it from a location behind and above it, as if the camera is following the plane.
  <!--[Follow-cam_View](./images/follow_cam_view1.png?raw=true)-->
  <img src='./images/follow_cam_view1.png' width=364px alt="Follow-cam_View" />
  <img src='./images/follow_cam_view2.png' width=364px alt="Follow-cam_View" />
  <!--[Follow-cam_View](./images/follow_cam_view2.png?raw=true)-->
* Helicopter-cam View
  * Here, the camera is movable with the mouse in an intuitive manner. Clicking and dragging should change the look angle, the up vector should remain up always,and the scroll wheel will move the camera closer or farther away from the scene.up vector should remain up always, and the scroll wheel will move the camera closer or farther away from the scene.
* Fixed-cam View
  * The Camera is fixed at the starting point of the game.
  <img src='./images/fixed_camera1.png' width=364px alt="Fixed-cam_View" />
  <img src='./images/fixed_camera2.png' width=364px alt="Fixed-cam_View" />
  <!--[Fixed-cam_View](./images/fixed_camera1.png?raw=true)-->
  <!--[Fixed-cam_View](./images/fixed_camera2.png?raw=true)-->

# Bonus
* Sounds have been added
* Compass on dashboard
* Segment Display for score
* Health Regeneration Power-Up

# Controls:

|      Moves      | Keyboard input  |
|:---------------:|:---------------:|
| Yaw       	  |    Q and E      |
| Pitch     	  |   UP and DOWN   |
| Roll       	  |    A and D      |
| Accelerate      |       W         |
| Retardation     |       S         |
| Fire Missile    | Left Mouse click|
| Drop Bomb       |Right Mouse click|
| Zoom In-Zoom Out|   Mouse Scroll  |
| Cam-view Toggle |       C         |
| Quit            |       Esc       |

		SO NOW IT'S TIME TO PLAY!!
								GOOD LUCK
