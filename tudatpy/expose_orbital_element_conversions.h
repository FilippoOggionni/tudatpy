//
// Created by ggarrett on 29-04-20.
//

#ifndef TUDATBUNDLE_EXPOSE_ORBITAL_ELEMENT_CONVERSIONS_H
#define TUDATBUNDLE_EXPOSE_ORBITAL_ELEMENT_CONVERSIONS_H

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include "Tudat/Astrodynamics/BasicAstrodynamics/orbitalElementConversions.h"
#include "Tudat/Astrodynamics/BasicAstrodynamics/stateVectorIndices.h"

namespace py = pybind11;
namespace toec = tudat::orbital_element_conversions;

namespace tudatpy {
    void expose_orbital_element_conversions(py::module &m);
}

#endif //TUDATBUNDLE_EXPOSE_ORBITAL_ELEMENT_CONVERSIONS_H