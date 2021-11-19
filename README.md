# Zooming animation on the Mandelbrot set
This project is based on the zooming animation on the Mandelbrot set.

Mandelbrot set is a set of complex numbers for which the function f<sub>c</sub>(z) = z^2 + c doesn't diverge to infinity when iterated from z=0.

I have implemented an optimised version of the Escape algorithm for making the representation of the Mandelbrot set. 
The use of basic real variables in 2D instead of the complex library for the representation of the points is for the sake of faster computing.
There's a function to color the points of the image in a beautiful manner based on the clarity of the image.
Multithreading is used in order to accelerate the process of generating the representation of the Mandelbrot set image.

# Usage
On starting the application by running the command ("bash run.sh") on Linux, (Use analogous commands for MacOS,Windows), the whole mandelbrot set image can be seen on the screen, for viewing the zooming application just click on the point at which you need to zoom in and the zooming animation begins zooming the image 2X times.
