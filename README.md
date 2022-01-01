# Boid-Simulation
 Boid simulation using personal engine

Changed SDL_Point to

```cpp
/**
 * The structure that defines a point (integer)
 *
 * \sa SDL_EnclosePoints
 * \sa SDL_PointInRect
 */
typedef struct SDL_Point
{
    int x;
    int y;

public:
    SDL_Point()
    {
        x = 0;
        y = 0;
    }
    SDL_Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void operator += (SDL_Point& otherPoint)
    {
        
        x += otherPoint.x;
        y += otherPoint.y;
 
    }

    void operator -= (SDL_Point& otherPoint)
    {

        x -= otherPoint.x;
        y -= otherPoint.y;
    }
} SDL_Point;
```
