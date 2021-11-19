#include<SFML/Graphics.hpp>
#include<iostream>
#include<thread>
using namespace std;

//Fixing the Resolution of the Screen
const int width=1920;
const int height=1080;

//total permutations of a RGB coloring
const int colorhe= (int) pow(256,3);

//Defining a Coloring scheme
tuple<int,int,int> pallete(int n,int max_iter){

    long double nn= (long double) n/ (long double) max_iter;
    int N=256;

    n=(int) (nn*(long double)colorhe);
    int b= n/N*N;
    int nn2= n-b*N*N;
    int r= nn2/N;
    int g= nn2-r*N;

    return tuple<int,int,int> (r,g,b);
}

// A function to create a Mandelbrot set 
void gen_mandelbrot(sf::VertexArray& va,int shift_x,int shift_y,int max_iter,float zoom,int id){
    
    //Figuring out which of the 8 parts does this thread has to compute
    int quo=id/4;
    int rem=id%4;
    
    for(int i=((quo)*(height/4));i<((quo+1)*(height/4));i++){
        for (int j=((rem)*(width/4));j<((rem+1)*(width/4));j++){
            
            //The scaled coordinate of the pixel
            long double x= ((long double)j -shift_x)/zoom;
            long double y= ((long double)i -shift_y)/zoom;
            
            //Doing this the basic algebraic way
            int n=0;

            //A substitute for coordinates of the point we need to plot
            long double x1=0.0;
            long double y1=0.0;
            
            long double x2=0.0;
            long double y2=0.0;

            for(int k=0;k<max_iter;k++){
                y1=2*x1*y1+y;
                x1=x2-y2+x;
                x2=x1*x1;
                y2=y1*y1;
                n++;

                if(x2+y2>4){
                    break;
                }
            }
            
            tuple<int,int,int> temp=pallete(n,max_iter);

            //Our pixel points array
            va[i*width+j].position=sf::Vector2f(j,i);
            sf::Color color(get<0>(temp),get<1>(temp),get<2>(temp));
            va[(i*width)+j].color=color;
        }

    }
}

int main(){
    sf::String title = "Mandelbrot_zoomer";
    sf::RenderWindow w(sf::VideoMode(width,height),title);
    
    w.setFramerateLimit(30);
    sf::VertexArray pixels(sf::Points,width*height);

    float zoom=200.0f;
    int max_iter=500; //The maximum number of iterations to carry out in order to make an image
    
    //Fixing the center point of the screen
    int shift_x=width/2;
    int shift_y=height/2;

    
    //Making the base still image and displaying it.
    vector<thread> threads(16);

    for(int i=0;i<16;i++){
        // gen_mandelbrot(pixels,shift_x,shift_y,max_iter,zoom,i);
        threads[i]=thread(gen_mandelbrot,ref(pixels),shift_x,shift_y,max_iter,zoom,i);
    }

    for(auto& th:threads){
        th.join();
    }
    // gen_mandelbrot(pixels,shift_x,shift_y,max_iter,zoom);
    w.clear();
    w.draw(pixels);
    w.display();

    //A boolean to check if the zooming animation has been initialised by clicking the Left Mouse button
    bool started=false;
    sf::Vector2i pos;
    while(w.isOpen()){
        sf::Event event;

        while(w.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                w.close();
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            started=true;
            pos= sf::Mouse::getPosition(w);
        }
        if(started){ 
            shift_x -= pos.x - shift_x;
            shift_y -= pos.y - shift_y;
            zoom*=2;
            max_iter+=10;

            for(int i=0;i<width*height;i++){
                pixels[i].color = sf::Color::Black;
            }
            for(int i=0;i<16;i++){
                threads[i]=thread(gen_mandelbrot,ref(pixels),shift_x,shift_y,max_iter,zoom,i);
            }
            for(auto&th :threads){
                th.join();
            }
            w.clear();
            w.draw(pixels);
            w.display();
        }
            
    }
    return 0;
}