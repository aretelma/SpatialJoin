/*
intersects
If a geometry or geography shares any portion of space then they intersect. 

intersection 
that portion of geometry A and geometry B that is shared between the two geometries.
*/

/*
ne_10m_urban_areas 
column # : 11878

ne_10m_admin_1_states_provinces
column # : 4596

src : https://github.com/nvkelso/natural-earth-vector/tree/master/10m_cultural
*/

SELECT count(*)
FROM ne_10m_admin_1_states_provinces tablesm, ne_10m_urban_areas
WHERE ST_Intersects(ne_10m_admin_1_states_provinces.geom, ne_10m_urban_areas.geom);

 count
-------
 13716


/*
usa_detailed_water_bodies
column # : 463,591
src : https://hub.arcgis.com/datasets/esri::usa-detailed-water-bodies/explore?location=29.227879%2C-113.614487%2C5.00

usa_block_group
column # : 239,203
src : https://hub.arcgis.com/datasets/CalEMA::usa-block-groups/explore?location=32.440137%2C-101.338027%2C5.00
*/


SELECT count(*)
FROM usa_detailed_water_bodies as water, usa_block_group as block
WHERE ST_Intersects(water.geom, block.geom);

 count
--------
 527195


 /*
 QGIS INTERSECTION
 */

SELECT count(*) FROM usa_inter;

 count
--------
 527195