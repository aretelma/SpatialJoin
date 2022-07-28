#include <iostream>

/* For geometry operations */
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/Geometry.h>
#include <libpq-fe.h>

#include <geos/io/WKTReader.h>

/* Geometry/GeometryFactory */
using geos::geom::Geometry;
using geos::geom::GeometryFactory;

/* WKTReader/WKTWriter */
using geos::io::WKTReader;

int main() {
    PGconn* conn1, * conn2; // database connect struct pointer
    PGresult* res1, * res2; // query result struct pointer
    int intersected = 0;
    int count = 0;
    int ntuples1, ntuples2;
    /* New factory with default (float) precision model */
    GeometryFactory::Ptr factory = GeometryFactory::create();


    /*
    * Reader requires a factory to bind the geometry to
    * for shared resources like the PrecisionModel
    */
    WKTReader reader(*factory);


    conn1 = PQsetdbLogin(NULL, NULL, NULL, NULL, "postGIS", "postgres", "1234");
    conn2 = PQsetdbLogin(NULL, NULL, NULL, NULL, "postGIS", "postgres", "1234");

    /*
    if (PQstatus(conn1) != CONNECTION_OK && PQstatus(conn2) != CONNECTION_OK) {
        std::cout << "CONNECTION ERROR";
        PQfinish(conn1);
        PQfinish(conn2);
        exit(1);
    }
    */
    res1 = PQexec(conn1, "select ST_ASTEXT(urban.geom) from ne_10m_urban_areas as urban tablesample bernoulli (10)"); // tablesample bernoulli (2)
    res2 = PQexec(conn2, "select ST_ASTEXT(states.geom) from ne_10m_admin_1_states_provinces as states tablesample bernoulli (10)");
    ntuples1 = PQntuples(res1);
    ntuples2 = PQntuples(res2);
    

    for (int i = 0; i < ntuples1; i++) {
        for (int j = 0; j < ntuples2; j++) {
            //std::cout << count++ << std::endl;
            std::unique_ptr<Geometry> geom_a(reader.read(PQgetvalue(res1, i, 0)));
            std::unique_ptr<Geometry> geom_b(reader.read(PQgetvalue(res2, j, 0)));
            if (geom_a->intersects(geom_b.get())) {
                intersected++;
                //std::cout << "=======================================" << std::endl;
                //std::cout << intersected << std::endl;
            }
        }
    }

    std::cout << "=======================================" << std::endl;
    std::cout << intersected;
    PQclear(res1);
    PQclear(res2);

    PQfinish(conn1);
    PQfinish(conn2);


    return 0;
}
