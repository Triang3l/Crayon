# Top-left rule

The top-left rule used by the Xenos for breaking the tie when the sample lies exactly on the edge of a triangle, rectangle or point sprite, is described in the [Direct3D 11.3 Functional Specification](https://microsoft.github.io/DirectX-Specs/d3d/archive/D3D11_3_FunctionalSpec.htm#3.4.2.1%20Top-Left%20Rule):

> Top edge: If an edge is exactly horizontal, and it is above the other edges of the triangle in pixel space, then it is a "top" edge.
>
> Left edge: If an edge is not exactly horizontal, and it is on the left side of the triangle in pixel space, then it is a "left" edge. A triangle can have one or two left edges.
>
> Top-Left Rule: If a sample location falls exactly on the edge of a triangle, the sample is inside the triangle if the edge is a "top" edge or a "left" edge. If two edges from the same triangle touch the pixel center, then if both edges are "top" or "left" then the sample is inside the triangle.

To apply the rule to the half-plane test, the translation term of the half-plane equation of the edge needs to be offset during the construction of the equations by 1 unit depending on the direction of the edge to produce the expected comparison result (which may be represented, for instance, by the sign of the distance between the sample and the edge) during the test.

The direction of the edge can be determined from the sign of one of the components of the perpendicular that has been made sure to be pointing either outward or inward depending on the convention regardless of the winding order (that is, one of the factors in the half-plane equation of the edge): the Y if the X is 0 (the edge is exactly horizontal), or the X otherwise.

This rule also means that the AABB of a primitive (which is essentially the primitive itself for a rectangle or a point sprite) has inclusive top and left extents and exclusive bottom and right extents.

# Edge half-plane test

**TODO:** Describe edge equation construction.

## x64 implementation

It is preferable for a negative signed distance to point inward into the triangle. This way, sample coverage can be obtained from the sign bits using `movemask_epi8`. In this case, a signed distance of 0 means outside, so top and left edges should be biased towards a negative signed distance. Because the perpendicular in the half-plane equation points outward in this case, it has a negative Y for a top edge, or a negative X for a left edge, so the sign of `x == 0 ? y : x` can be right-shifted into the least significant bit to produce the tie-break offset.

For the purposes of the test itself, the sign of the translation term of the equation shouldn't be significant, because SSE2 `psubq` performs `destination = destination - source`, so it can directly subtract the translation term of the equation from the signed distance accumulator.
