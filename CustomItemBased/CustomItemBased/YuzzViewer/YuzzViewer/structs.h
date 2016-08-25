#ifndef __STRUCTS_H__
#define __STRUCTS_H__

struct BANANA_INFO 
{
    double  CenterX{0};  //annulus center point x
    double  CenterY{0};  //annulus center point y
    double	InnerRad{1180.5342318566909};	// annulus inner radius, in millimeters
    double	OuterRad{1666.7078604028079};	// annulus outer radius, in millimeters
    double	ThetaMin{0};  //  low angle limit of stripe
    double	Spread{1.3529000000000000};		// spread of wedge sides, in radians
    int		Segments{100};	// number of line segments in arc
    float	Depth{600};		// depth in Z axis, in millimeters
    int		Type{1};	// robot scan mode type
};

#endif
