#include "framebuffer.h"

#include <stdlib.h>



int framebuffer_init( framebuffer* fb,
                      unsigned int width, unsigned int height )
{
    if( !fb )
        return 0;

    fb->width  = width;
    fb->height = height;

    /* try to allocate the color buffer */
    fb->color = malloc( width*height*4 );

    if( !fb->color )
        return 0;

    /* try to allocate the depth buffer */
    fb->depth = malloc( width*height*sizeof(float) );

    if( !fb->depth )
    {
        free( fb->color );
        return 0;
    }

    return 1;
}

void framebuffer_cleanup( framebuffer* fb )
{
    if( fb )
    {
        free( fb->depth );
        free( fb->color );
    }
}

void framebuffer_clear( framebuffer* fb, unsigned char r, unsigned char g,
                                         unsigned char b, unsigned char a )
{
    unsigned int i, count;
    unsigned char* ptr;

    if( fb )
    {
        count = fb->height*fb->width;

        for( ptr=fb->color, i=0; i<count; ++i, ptr+=4 )
        {
            ptr[ RED   ] = r;
            ptr[ GREEN ] = g;
            ptr[ BLUE  ] = b;
            ptr[ ALPHA ] = a;
        }
    }
}

void framebuffer_clear_depth( framebuffer* fb, float value )
{
    unsigned int i, count;
    float* ptr;

    if( fb )
    {
        count = fb->height*fb->width;
        value = value<0.0f ? 0.0f : (value>1.0f ? 1.0f : value);

        for( ptr=fb->depth, i=0; i<count; ++i, ++ptr )
        {
            *ptr = value;
        }
    }
}

