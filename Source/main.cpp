#include <SDL2/SDL.h>
//#include <GL/glew.h>

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include <SDL2/SDL_opengl.h>

#include <assert.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <thread>

#include "../Inc/AStarSearch.hpp"
#include "../Inc/Renderer.hpp"
#include "../Inc/Utility.hpp"
#include "../Inc/Config.hpp"
#include "./Utilities/cJSON.h"


//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FRAMES_PER_SECOND = 60;


bool quit = false;
bool success = true;
int frame = 0;


LTimer fps_timer;

RGBColor defaultColor = RGBColor::black;

std::vector<std::shared_ptr<MapLocation>> grid_locations;

void move_object(Renderer* renderer, SDL_Rect& object, SDL_Point delta_pos)
{
    object.x += delta_pos.x;
    object.y += delta_pos.y;
    renderer->addToRenderQueue(object, RGBColor::red);
}

void fall_down(Renderer* renderer, SDL_Rect& object)
{
    renderer->addToRenderQueue(object, RGBColor::blue);
}

void generate_tilemap(SDL_Renderer* renderer)
{
    float tile_width = 64;
    float tile_height = 64;
    
    for (int x = 0; x < SCREEN_WIDTH; x += tile_width)
    {
        for (int y = 0; y < SCREEN_HEIGHT; y += tile_height)
        {
            SDL_Rect rect;
            rect.x = x;
            rect.y = y;
            rect.w = tile_width;
            rect.h = tile_height;
        }
    }
}

GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;


int main( int argc, char* args[] )
{
    auto cfg = new Config();
    ifstream file;
    file.open("./Utilities/config.json");
    std::string temp;
    std::string contents;
    while(std::getline(file, temp))
    {
        contents += temp;
    }

    //std::cout << "Temp string is "<< contents << std::endl;
    file.close();
            
    Document doc;
    cfg->read(contents.c_str(), doc);
    assert(doc.IsObject());
    assert(doc.HasMember("name"));
    assert(doc["job"].IsString());



	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window

    //The window renderer
    SDL_Renderer* gRenderer = NULL;
    
    SDL_Rect playerRect;
    playerRect.x = 0;
    playerRect.y = 300;
    playerRect.h = 30.0f;
    playerRect.w = 30.0f;

    
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );


	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		window = SDL_CreateWindow( "Path Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

        auto gl_context = SDL_GL_CreateContext(window);

        //Use Vsync
        if( SDL_GL_SetSwapInterval( 1 ) < 0 )
        {
            printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
        }

		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
            gRenderer = SDL_CreateRenderer(window, 1, SDL_RENDERER_ACCELERATED);
            Renderer* renderer = new Renderer(gRenderer);

            auto text = renderer->loadTexture("../Assets/Images/astro_atlas.png");

            std::vector<int> seq {1,2,3,4,5,6,7};   
            auto astroRun = new SpriteSheet(gRenderer, text, Parser::ParseFile("../Assets/Images/astro_atlas.json"), seq, 1.0f);
            auto texture = renderer->loadTexture("../Assets/Images/astro_atlas.png");
            
          //  sSheet->RenderFrame(texture, &src, &dest);

          //  Graph* graph = new Graph(grid_locations);
            //std::unique_ptr<Graph> graph (new Graph(grid_locations));

            float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f,  0.5f, 0.0f
            };
            
            //openGL
            //glGenBuffers(1, &gVBO);
            //glBindBuffer(GL_ARRAY_BUFFER, gVBO);
            //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            const GLchar* vertexShaderSource[] =
            {
                " #version 150 core layout (location = 0) in vec3 aPos; void main() { gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); } "
                //"#version 330 core vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
            };

            GLuint vertexShader;
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            
            glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
            glCompileShader(vertexShader);

            int  success;
            char infoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

            if(!success)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            if (gRenderer == NULL)
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
                return 1;
            }

            SDL_Event e;

            int current_key = 0;
            int last_key = 0;
            float speed = 0;
            float multiplier = 0.1f;
            int successful_button_pushes = 0;
            
            fps_timer.start();
            
            int frame_second = 0;

            while(!quit)
            {
                //---fps cap---//
                if (fps_timer.getTicks() < (1000 / FRAMES_PER_SECOND)) continue;
                frame_second += fps_timer.getTicks();
                
                if (frame >= FRAMES_PER_SECOND && frame_second <= 1000) continue;

                fps_timer.stop();
                fps_timer.start();
                 //---fps cap end---//
                
                if (frame_second >= 1000)
                {
                    frame = 0;
                    frame_second = 0;
                }

                //printf("Current frame %i \n ", frame);
                
                //handle sdl event queue
                while(SDL_PollEvent( &e ) != 0)
                {
                    if (e.type == SDL_KEYDOWN)
                    {
                        if (e.key.keysym.sym == SDLK_x || e.key.keysym.sym == SDLK_c)
                        {
                            
                            (e.key.keysym.sym == SDLK_x) ? current_key = 1 : current_key = -1;
                            
                            if (current_key == last_key)
                            {
                                printf("Fall down \n ");
                                fall_down(renderer, playerRect);
                                last_key = current_key;
                                successful_button_pushes = 0;
                                speed = 0;
                                continue;
                            }
                            
                            successful_button_pushes += 1;
                            speed += successful_button_pushes * multiplier;
                            last_key = current_key;
                        }
                        
                        switch (e.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                quit = true;
                                break;

                            case SDLK_q:
                                quit = true;
                                break;

                            case SDLK_r:
                                astroRun->Render();
                                break;

                            default:
                                break;
                        }
                    }
                }
                
                speed -= 0.05f;
                if (speed <= 0) speed = 0;
                
                SDL_Point delta_move;
                delta_move.x = speed;
                delta_move.y = 0;
                move_object(renderer, playerRect, delta_move);
            
                //renderer->update();
                //SDL_UpdateWindowSurface( window );
                //
                SDL_RenderPresent(gRenderer);
                frame++;
            }
            
            SDL_DestroyWindow( window );
            SDL_DestroyRenderer(gRenderer);

            SDL_Quit();
		}
	}

	return 0;
}
