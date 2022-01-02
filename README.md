# Boid-Simulation
 Boid simulation using personal engine

Changed SDL_Point in SDL_rect.h to

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

    SDL_Point operator + (SDL_Point& otherPoint)
    {
        SDL_Point p;
        p.x = x + otherPoint.x;
        p.y = y + otherPoint.y;
        return p;
    }

    SDL_Point operator - (SDL_Point& otherPoint)
    {
        SDL_Point p;
        p.x = x - otherPoint.x;
        p.y = y - otherPoint.y;
        return p;
    }

    SDL_Point operator * (int scalar)
    {
        SDL_Point p;
        p.x = x * scalar;
        p.y = y * scalar;
        return p;
    }

    SDL_Point operator / (int scalar)
    {
        SDL_Point p;
        p.x = x / scalar;
        p.y = y / scalar;
        return p;
    }

 
} SDL_Point;
```

Changed SDL_FPoint in SDL_rect.h to

```cpp

/**
 * The structure that defines a point (floating point)
 *
 * \sa SDL_EnclosePoints
 * \sa SDL_PointInRect
 */
typedef struct SDL_FPoint
{
    float x;
    float y;

    SDL_FPoint()
    {
        x = 0.0f;
        y = 0.0f;
    }
    SDL_FPoint(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    void operator += (SDL_FPoint& otherPoint)
    {

        x += otherPoint.x;
        y += otherPoint.y;

    }

    void operator -= (SDL_FPoint& otherPoint)
    {

        x -= otherPoint.x;
        y -= otherPoint.y;
    }


    SDL_FPoint operator + (SDL_FPoint& otherPoint)
    {
        SDL_FPoint p;
        p.x = x + otherPoint.x;
        p.y = y + otherPoint.y;
        return p;
    }

    SDL_FPoint operator - (SDL_FPoint& otherPoint)
    {
        SDL_FPoint p;
        p.x = x - otherPoint.x;
        p.y = y - otherPoint.y;
        return p;
    }

    SDL_FPoint operator * (float scalar)
    {
        SDL_FPoint p;
        p.x = x * scalar;
        p.y = y * scalar;
        return p;
    }

    SDL_FPoint operator / (float scalar)
    {
        SDL_FPoint p;
        p.x = x / scalar;
        p.y = y / scalar;
        return p;
    }


} SDL_FPoint;
```
