# Photon Mapping

Personal Computer Graphics Project: Physically Based Rendering. 

## Renders

White glass teapot and reflective sphere

![](renders/teapot_glass_white_3AA.png)

------
Yellow glass dragon and mirror wall(reflective)

![](renders/dragon_glass_yellow_3AA_near.png)
![](renders/dragon_glass_yellow_3AA_far.png)

## Roadmap

* [x] **Kd-Tree** Acceleration Structure, lookup photons
* [x] **Multi-thread** shooting photon tasks
* [x] **LPhoton** and **EPhoton** calculation
* [x] **Caustic, indirect and radiance** photon calculation and storage
* [ ] Complicated material implementation
* [ ] Double check Fresnel and reflection models
* [ ] Final gathering and indirect lighting
 

## Other renders
Yellow glass teapot, specular transmissive sphere and reflective wall

![](renders/teapot_glass_yellow_sphere_3AA.png)

Glass material is implemented using weighted-material combined with specular transmission and specular reflection.

------
Specular transmission teapot

![](renders/teapot_transmissive_white_3AA.png)

Teapot is perfectly tramsmissive, the caustic effect can be well captured using photon mapping.

Transmissive teapot and reflective back wall 

![](renders/teapot_transmissive_back_mirror_3AA.png)


------
Prism with 80% reflection and 20% transmission material

![](renders/prism_glass_3AA.png)

Both caustic and reflective effects can be captured in this test scene.


## IN PROGRESS 
Final gathering for indirect lighting

![](renders/FinalGather.png)


## Debug Renders
Test for kd-tree and photon shooting tasks

![](renders/bloopers_debug/100Lookup_0.2MaxDist.png)

------
Render with radiance map ONLY

![](renders/bloopers_debug/UseRadianceMapDirectly.png)

