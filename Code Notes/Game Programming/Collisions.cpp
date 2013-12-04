﻿//////////////////////////////////////////////////////////////////////////////
//COLLISIONS
//////////////////////////////////////////////////////////////////////////////
/*
PERFECTLY ELASTIC COLLISION: 
collision with no loss of energy

COLLISION DETECTION: 
Detection/prediction of collision of objects

COLLISION RESOLUTION: 
Physics rules applied to the colliding objects as a result of the event

COLLISION EFFECTS: 
Events that arise as a result of the collision

CONSTRAINT BASED METHODS: 
Complex offline collision detection

IMPULSE BASED METHODS: 
Use impulse generated by collision to determine resulting velocities

//////////////////////////////////////////////////////////////////////////////
//COLLISION DETECTION
//////////////////////////////////////////////////////////////////////////////

Once proxies are tested, to obtain greater accuracies, 
object A and B are colliding if:

 ---------
| u.n < 0 | angle Ɵ > 90
 ---------
 u = relative velocity of vertex Pᵃ of A colliding with B
 n = normal to the plane of collsion

 Vertex-Face: Plane of collision is face
 Vertex-Edge/Vertex: Plane of collsion contains edge and is ⊥ to shortest 
                     vector from origin to edge


==============================================================================
BOUNDING MESH PROXIES
==============================================================================
SPHERE: Center position vector, Radius
BOX: Center position vector, MinBounds/MaxBounds vectors

MinBounds: bottom near left coordinate
MaxBounds: top far right coordinate

    minBounds.x = Center.x - (width/2);
    minBounds.y = Center.y - (height/2);
    minBounds.z = Center.z - (depth/2);
    maxBounds.x = Center.x + (width/2);
    maxBounds.y = Center.y + (height/2);
    maxBounds.z = Center.z + (depth/2);

==============================================================================
SPHERE-SPHERE COLLISION ALGORITHM
==============================================================================

    FLOAT3 ballToBall = p1 - p2;
    float distance = (ballToBall.x * ballToBall.x) + 
                     (ballToBall.y * ballToBall.y) + 
                     (ballToBall.z * ballToBall.z);
    float minDistance = r1 + r2;
    if((minDistance*minDistance) > distance)
        return true;
    return false;

==============================================================================
SPHERE-PLANE COLLISION ALGORITHM
==============================================================================
- Get normalized vector from sphere center pointing to plane center
- Times by radius to get length from sphere center to edge of sphere in 
  direction of box
- Vector addition to get vector from origon to point on sphere closest 
  to plane

N.(F – P) = 0  holds true for any point F on the plane; P is point on plane
N = Plane->Normal
F = SphereVector
P = Plane->Center

    D3DXVECTOR3 SphereCenterToPlane = Plane->Center - Sphere->Center;
    D3DXVec3Normalize(&SphereCenterToPlane,&SphereCenterToPlane);
    D3DXVECTOR3 SphereVector = Sphere->Radius * SphereCenterToPlane;
    SphereVector = SphereVector + Sphere->Center;

    D3DXVECTOR3 SphereToPlane = SphereVector - Plane->Center;
    float amount = D3DXVec3Dot(&Plane->Normal,&SphereToPlane);
    if(amount <= 0)
        return true; //0 = point is on the plane; 
                     //<0 = point is behind the plane
    else
        return false; // >0 = point is before the plane

==============================================================================
SPHERE-POINT COLLISION ALGORITHM
==============================================================================
Get vector from sphere center to point and find distance
If distance is less then radius distance then the point is inside the sphere

    D3DXVECTOR3 vec = Sphere->Center - Point->Center;
    float dist = (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
    if(dist <= (pow(Sphere->Radius,2)))
        return true;
    else
        return false;

==============================================================================
SPHERE-LINE COLLISION ALGORITHM
==============================================================================

FLOAT3 P0,P1                                //points on each end of line
FLOAT3 d = P1 - P0;                         //vector along the line
FLOAT3 LineToSphere = SphereCenter - P0;    //vector from sphere to line
FLOAT3 normal                               //normal for line

//CHECK BODY
//n.(SphereCenter-P0) = dis from line
float distance = (normal.normalize).dot(LineToSphere);  
float magdistance = GetMagnitude(distance);
if(magdistance < radius)
{
    //SPHERE iS INSIDE LINE; CHECK ENDS (Get position of collision on line)
    FLOAT3 colPosition = SphereCenter - (distance*normal.normalize);

    //FIND VALUE OF T (colPosition = P0 + td parametric line equation)
    float t;
    if(d.x == 0)
        t = (colPosition.y - P0.y)/d.y;
    else
        t = (colPosition.x - P0.x)/d.x;

    if(t > 1) //if past the end of the line
    {
        if((SphereCenter-P1).length() > radius))
            return false;
    }
    else if(t < 0)  //if before the start of the line
    {
        if((SphereCenter-P0).length() > radius))
            return false;
    }
    return true;
}
return false;


==============================================================================
BOX-BOX COLLISION ALGORITHM
==============================================================================

OBB: OBJECT ALIGNED BOUNDING BOX
Box rotates with object and aligned to its axis

AABB: AXIS ALIGNED BOUNDING BOX
Box sides are aligned with the world axis

if(BoxA->max.x < BoxB->min.x || BoxA->min.x > BoxB->max.x)
    return false;
if(BoxA->max.y < BoxB->min.y || BoxA->min.y > BoxB->max.y)
    return false;
if(BoxA->max.z < BoxB->min.z || BoxA->min.z > BoxB->max.z)
    return false;
else
    return true;

==============================================================================
PLANE-RAY COLLISION ALGORITHM
==============================================================================

Ray: P₀(x,y,z) with d(dx,dy,dz)
Plane: n̂(a,b,c)

1) Determine if ray will intersect plane
     
     if d.n̂ > 0 collision
     if d.n̂ < 0 no collision

2) Get t amount along ray

    C = A/cosƟ from trig
    ⁂ t = (P₁-P₀).n̂/cosƟ    

    a.b̂ = ‖a‖cosƟ from projection
    ⁂ d.n̂ = ‖d‖cosƟ
    ⁂ cosƟ = d.n̂/‖d‖
    ⁂ cosƟ = d.n̂

    ⁂ t = (P₁-P₀).n̂ / d.n̂

    Point on plane P(t) ray will collide with:
    P(t) = P₀ + td

==============================================================================
POINT-LINE COLLISION
==============================================================================

bool selectedEdge = false;
for (int i = 0; i < EDGE.EdgeList.Count; i++)
{
    //vector along line from start to end
    float lx = EDGE.EdgeList[i].start.X - EDGE.EdgeList[i].end.X;
    float ly = EDGE.EdgeList[i].start.Y - EDGE.EdgeList[i].end.Y;
    float nx = ly;
    float ny = -lx;
    float vx = e.X - EDGE.EdgeList[i].end.X;    //po to p1
    float vy = e.Y - EDGE.EdgeList[i].end.Y;

    //normalize normal
    double length = Math.Sqrt((double)((nx*nx)+(ny*ny)));
    nx = (float)(nx/length);
    ny = (float)(ny/length);

    //get magnitude distance (p1-p0).n = dis
    float distance = (vx * nx) + (vy * ny);
    if (distance < 0) { distance *= -1; }

    if (distance < MinMouseDistance)
    {
        //check bounds n (l is pointing towards start node, use end as P0)
        //P(t) = P(o) + td
        //t = (P(t)x - P(o)x)/dx
        if (lx != 0)
        {
            float t = ((float)(e.X - EDGE.EdgeList[i].end.X)) / lx;
            if ((t < 0) || (t > 1))
                continue;
        }
        else if (ly != 0)
        {
            float t = ((float)(e.Y - EDGE.EdgeList[i].end.Y)) / ly;
            if ((t < 0) || (t > 1))
                continue;
        }
        else
            continue;

        //FOUND EDGE
        return;
    }
}
==============================================================================
PLANE-POINT COLLISION
==============================================================================

- Input point position into P(t) and rearrange to find t
- u1 and u2 are vectors spanning full sides of plane
- if value of t is between 0 and 1, point is inside plane

float t,s;
for(unsigned int i = 0; i < tiles.size(); i++)
{
    TILE*T = &tiles[i];
    if(!T->active)
        continue;
    if(!T->IsOnScreen())
        continue;

    //Mouse-tile collision testing
    t = (((input->mouseY-T->P0.y)/T->u1.y)-((input->mouseX-T->P0.x)/T->u1.x))
        /((T->u2.y/T->u1.y)-(T->u2.x/T->u1.x));

    if((t >= 0)&&(t <= 1.0f))
    {
        s = ((input->mouseX - T->P0.x)/T->u1.x)-((t*T->u2.x)/T->u1.x);
        if((s >= 0)&&(s <= 1.0f))
        {
            //clicked on tile
            ChangeSelection(T);
            return true;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
//CONVEX/CONCAVE COLLISION DETECTION
//////////////////////////////////////////////////////////////////////////////

==============================================================================
LINE-INTERSECTION TECHNIQUE (LINE-LINE COLLISION)
==============================================================================
supports concave/convex shapes
slow and ineffecient

1) For each outside edge of the model, create a line
2) Test this array of lines against other model's array of lines for each line

Line1: P₁(t) = P₁(0) + t₁d₁
Line2: P₂(t) = P₂(0) + t₂d₂
where d = vector between start/end point of line
where t = 0->1 when on the line

Collision occurs if both t₁ and t₂ are between 0 and 1

P₁(0) + t₁d₁ = P₂(0) + t₂d₂

⁂ P₁(0)x + t₁d₁x = P₂(0)x + t₂d₂x
⁂ P₁(0)y + t₁d₁y = P₂(0)y + t₂d₂y

and rearrange to solve for t₁ and t₂

==============================================================================
GJK COLLISION ALGORITHM
==============================================================================

MINKOWSKI DIFFERENCE:
- Create from two convex hulls by subtracting all points of A from all points of B
- If contains the origin, both hulls are colliding
- As hulls get closer, Minkowski Difference hull gets closer to origin

GJK ALGORITHM:
- Doesn't require computing whole Minkowski Difference hull
- Builds a simplex inside the Minkowski Difference to see if it encloses the origin
- Uses a 'support' function to find the furthest point in the MD hull in a direction
  which helps create the simplex with the largest area enclosing the MD hull

CHOOSING THE INITIAL POINTS:
• Randomly choose a point in A and B and subract to get a direction between the two
• Find any points along that direction that are the furthest away (+ largest dot product)
• Generate the Minkowski Difference point of the chosen two points which is an edge point 
• Negate the direction

WHILE COLLISION IS NOT FOUND:
• Get a new edge point in the direction
• Check if this new point is past the origin (has a + dot product with it)
• If not past the origin, origin isn't inside the difference and collision cannot occur
• If line simplex: Cross the line and the last point to origin to get the next direction
• If a tri-plane simplex: Next direction is the normal that points towards the origin
• If a tetrahedron simplex: 
    - If origin is inside all three planes (the forth was checked as a tri plane) then collision
    - If origin is outside a plane, remove the furthest point
    - The next direction is the normal to the plane towards the origin

//////////////////////////////////////////////////////////////////////////////
//COLLISION RESOLUTION
//////////////////////////////////////////////////////////////////////////////

 ---------------
| uᶠ.n = -euⁱ.n |
 ---------------
 uⁱ/uᶠ = relative velocity before/after collision
 n = plane of collision
 e = amount of energy lost during collision where 0 ≤ e ≤ 1
     e = 1; pefectly elastic collision
     e = 0; all energy lost and objects stop

 When storing object's mass, only store ¹/m
 For collisions involving large static objects, set objects mass to ¹/∞

==============================================================================
NON-ROTATING OBJECTS
==============================================================================
 -----------
| u = vᵃ-vᵇ | 
 -----------
 u = Relative velocity of vertex Pᵃ on A which collides with object B
 vᵃ,vᵇ = Linear velocity = Translational velocity

RESULT IN COLLISION: 

change in velocity for A and B
 --------------------------
| vᵃ(f) = vᵃ(i) + (¹/mᵃ)Jn |
| vᵇ(f) = vᵇ(i) - (¹/mᵇ)Jn |
 --------------------------
Use these values and uᶠ.n = -euⁱ.n to find equation for impulse(J) 


==============================================================================
ROTATING OBJECTS
==============================================================================

 -----------
| u = vᵃ-vᵇ | 
 -----------
 u = Relative velocity of vertex Pᵃ on A which collides with object B
 vᵃ/vᵇ = Linear velocity 
       = Translational(translation) + Tangential velocity(rotation)
         v = vᵗ + vᵀ = vᵗ + w X r

RESULT IN COLLISION: 

change in translational velocity for A and B
 --------------------------
| vᵗᵃ(f) = vᵃ(i) + (¹/mᵃ)Jn |
| vᵗᵇ(f) = vᵇ(i) - (¹/mᵇ)Jn |
 --------------------------
change in angular velocity for A and B
 --------------------------------
| wᵃ(f) = wᵃ(i) + (¹/iᵃ)(r X Jn) |
| wᵇ(f) = wᵇ(i) - (¹/iᵇ)(r X Jn) |
 --------------------------------
 Use these values to find equation for impulse(J)

 *///////////////////////////////////////////////////////////////////////////////