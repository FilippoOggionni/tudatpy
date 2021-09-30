/*    Copyright (c) 2010-2021, Delft University of Technology
 *    All rights reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "expose_estimated_parameter_setup.h"

#include "tudat/simulation/estimation_setup/createEstimatableParameters.h"

#include "tudatpy/docstrings.h"

namespace tep = tudat::estimatable_parameters;
namespace tss = tudat::simulation_setup;

namespace tudatpy {
namespace simulation {
namespace estimation_setup {
namespace parameter {

void expose_estimated_parameter_setup(py::module &m) {


    py::enum_<tep::EstimatebleParametersEnum >(m, "EstimatebleParameterTypes")
            .value("arc_wise_initial_body_state_type", tep::EstimatebleParametersEnum::arc_wise_initial_body_state)
            .value("initial_body_state_type", tep::EstimatebleParametersEnum::initial_body_state)
            .value("initial_rotational_body_state_type", tep::EstimatebleParametersEnum::initial_rotational_body_state)
            .value("gravitational_parameter_type", tep::EstimatebleParametersEnum::gravitational_parameter)
            .value("constant_drag_coefficient_type", tep::EstimatebleParametersEnum::constant_drag_coefficient)
            .value("radiation_pressure_coefficient_type", tep::EstimatebleParametersEnum::radiation_pressure_coefficient)
            .value("arc_wise_radiation_pressure_coefficient_type", tep::EstimatebleParametersEnum::arc_wise_radiation_pressure_coefficient)
            .value("spherical_harmonics_cosine_coefficient_block_type", tep::EstimatebleParametersEnum::arc_wise_initial_body_state)
            .value("spherical_harmonics_sine_coefficient_block_type", tep::EstimatebleParametersEnum::spherical_harmonics_sine_coefficient_block)
            .value("constant_rotation_rate_type", tep::EstimatebleParametersEnum::constant_rotation_rate)
            .value("rotation_pole_position_type", tep::EstimatebleParametersEnum::rotation_pole_position)
            .value("constant_additive_observation_bias_type", tep::EstimatebleParametersEnum::constant_additive_observation_bias)
            .value("arcwise_constant_additive_observation_bias_type", tep::EstimatebleParametersEnum::arcwise_constant_additive_observation_bias)
            .value("constant_relative_observation_bias_type", tep::EstimatebleParametersEnum::constant_relative_observation_bias)
            .value("arcwise_constant_relative_observation_bias_type", tep::EstimatebleParametersEnum::arcwise_constant_relative_observation_bias)
            .value("ppn_parameter_gamma_type", tep::EstimatebleParametersEnum::ppn_parameter_gamma)
            .value("ppn_parameter_beta_type", tep::EstimatebleParametersEnum::ppn_parameter_beta)
            .value("ground_station_position_type", tep::EstimatebleParametersEnum::ground_station_position)
            .value("equivalence_principle_lpi_violation_parameter_type", tep::EstimatebleParametersEnum::equivalence_principle_lpi_violation_parameter)
            .value("empirical_acceleration_coefficients_type", tep::EstimatebleParametersEnum::empirical_acceleration_coefficients)// TO EXPOSE
            .value("arc_wise_empirical_acceleration_coefficients_type", tep::EstimatebleParametersEnum::arc_wise_empirical_acceleration_coefficients)// TO EXPOSE
            .value("full_degree_tidal_love_number_type", tep::EstimatebleParametersEnum::full_degree_tidal_love_number)// TO EXPOSE
            .value("single_degree_variable_tidal_love_number_type", tep::EstimatebleParametersEnum::single_degree_variable_tidal_love_number)
            .value("direct_dissipation_tidal_time_lag_type", tep::EstimatebleParametersEnum::direct_dissipation_tidal_time_lag)
            .value("mean_moment_of_inertia_type", tep::EstimatebleParametersEnum::mean_moment_of_inertia)
            .value("arc_wise_constant_drag_coefficient_type", tep::EstimatebleParametersEnum::arc_wise_constant_drag_coefficient)
            .value("periodic_spin_variation_type", tep::EstimatebleParametersEnum::periodic_spin_variation)
            .value("polar_motion_amplitude_type", tep::EstimatebleParametersEnum::polar_motion_amplitude)
            .value("core_factor_type", tep::EstimatebleParametersEnum::core_factor)
            .value("free_core_nutation_rate_type", tep::EstimatebleParametersEnum::free_core_nutation_rate)
            .value("desaturation_delta_v_values_type", tep::EstimatebleParametersEnum::desaturation_delta_v_values)
            .export_values();

    py::class_<tep::EstimatableParameterSettings,
            std::shared_ptr<tep::EstimatableParameterSettings>>(m, "EstimatableParameterSettings")
            .def(py::init<
                 const std::string,
                 const tep::EstimatebleParametersEnum,
                 const std::string>(),
                 py::arg("associated_body"),
                 py::arg("parameter_type"),
                 py::arg("point_on_body_id") = "");

    m.def("initial_states",
          &tss::getInitialStateParameterSettings< double >,
          py::arg("propagator_settings"), py::arg("bodies") );

    m.def("gravitational_parameter",
          &tep::gravitationalParameter,
          py::arg("body_name") );


    m.def("spherical_harmonics_c_coefficients",
          py::overload_cast< const std::string,
          const int,
          const int,
          const int,
          const int >(&tep::sphericalHarmonicsCosineBlock),
          py::arg("body_name"),
          py::arg("minimum_degree"),
          py::arg("minimum_order"),
          py::arg("maximum_degree"),
          py::arg("maximum_order") );

    m.def("spherical_harmonics_c_coefficients",
          py::overload_cast< const std::string,
          std::vector< std::pair< int, int > > >( &tep::sphericalHarmonicsCosineBlock),
          py::arg("body_name"),
          py::arg("block_indices") );

    m.def("spherical_harmonics_s_coefficients",
          py::overload_cast< const std::string,
          const int,
          const int,
          const int,
          const int  >(&tep::sphericalHarmonicsSineBlock),
          py::arg("body_name"),
          py::arg("minimum_degree"),
          py::arg("minimum_order"),
          py::arg("maximum_degree"),
          py::arg("maximum_order") );

    m.def("spherical_harmonics_s_coefficients",
          py::overload_cast< const std::string,
          std::vector< std::pair< int, int > > >( &tep::sphericalHarmonicsSineBlock),
          py::arg("body_name"),
          py::arg("block_indices") );


    m.def("constant_drag_coefficient",
          &tep::constantDragCoefficient,
          py::arg("body_name") );


    m.def("radiation_pressure_coefficient",
          &tep::radiationPressureCoefficient,
          py::arg("body_name") );

    m.def("arcwise_radiation_pressure_coefficient",
          &tep::arcwiseRadiationPressureCoefficient,
          py::arg("body_name"),
          py::arg("arc_initial_times") );

    m.def("arcwise_drag_coefficient",
          &tep::arcwiseDragCoefficient,
          py::arg("body_name"),
          py::arg("arc_initial_times") );

    m.def("constant_rotation_rate",
          &tep::constantRotationRate,
          py::arg("body_name") );

    m.def("rotation_pole_position",
          &tep::rotationPolePosition,
          py::arg("body_name") );

    m.def("observation_bias",
          &tep::observationBias,
          py::arg("link_ends"),
          py::arg("observable_type") );

    m.def("relative_observation_bias",
          &tep::relativeObservationBias,
          py::arg("link_ends"),
          py::arg("observable_type") );

    m.def("arcwise_observation_bias",
          &tep::arcwiseObservationBias,
          py::arg("link_ends"),
          py::arg("observable_type"),
          py::arg("arc_start_times" ),
          py::arg("time_link_end" ) );

    m.def("arcwise_relative_observation_bias",
          &tep::arcwiseRelativeObservationBias,
          py::arg("link_ends"),
          py::arg("observable_type"),
          py::arg("arc_start_times" ),
          py::arg("time_link_end" ) );


    m.def("ppn_parameter_gamma",
          &tep::ppnParameterGamma );

    m.def("ppn_parameter_beta",
          &tep::ppnParameterBeta );

    m.def("ground_station_position",
          &tep::groundStationPosition,
          py::arg("body_name"),
          py::arg("ground_station_name") );

    m.def("direct_tidal_dissipation_time_lag",
          py::overload_cast< const std::string&, const std::string& >(
              &tep::directTidalDissipationLagTime ),
          py::arg("body_name"),
          py::arg("deforming_body") );

    m.def("direct_tidal_dissipation_time_lag",
          py::overload_cast< const std::string&, const std::vector< std::string >& >(
              &tep::directTidalDissipationLagTime ),
          py::arg("body_name"),
          py::arg("deforming_body") );

    m.def("mean_moment_of_inertia",
          &tep::meanMomentOfInertia,
          py::arg("body_name") );

    m.def("order_invariant_k_love_number",
          py::overload_cast< const std::string&,
          const int,
          const std::string,
          const bool >(&tep::orderInvariantKLoveNumber),
          py::arg("deformed_body"),
          py::arg("degree"),
          py::arg("deforming_body"),
          py::arg("use_complex_love_number") = 0 );

    m.def("order_invariant_k_love_number",
          py::overload_cast< const std::string&,
          const int,
          const std::vector< std::string >&,
          const bool >(&tep::orderInvariantKLoveNumber),
          py::arg("deformed_body"),
          py::arg("degree"),
          py::arg("deforming_bodies"),
          py::arg("use_complex_love_number") = 0 );

    m.def("order_invariant_k_love_number",
          py::overload_cast< const std::string&,
          const int,
          const bool >(&tep::orderInvariantKLoveNumber),
          py::arg("deformed_body"),
          py::arg("degree"),
          py::arg("use_complex_love_number") = 0 );



    m.def("order_varying_k_love_number",
          py::overload_cast< const std::string&,
          const int,
          const std::vector< int >&,
          const std::string,
          const bool >(&tep::orderVaryingKLoveNumber),
          py::arg("deformed_body"),
          py::arg("degree"),
          py::arg("orders"),
          py::arg("deforming_body"),
          py::arg("use_complex_love_number") = 0 );

    m.def("order_varying_k_love_number",
          py::overload_cast< const std::string&,
          const int,
          const std::vector< int >&,
          const std::vector< std::string >&,
          const bool >(&tep::orderVaryingKLoveNumber),
          py::arg("deformed_body"),
          py::arg("degree"),
          py::arg("orders"),
          py::arg("deforming_bodies"),
          py::arg("use_complex_love_number") = 0 );

    m.def("order_varying_k_love_number",
          py::overload_cast< const std::string&,
          const int,
          const std::vector< int >&,
          const bool >(&tep::orderVaryingKLoveNumber),
          py::arg("deformed_body"),
          py::arg("degree"),
          py::arg("orders"),
          py::arg("use_complex_love_number") = 0 );

    m.def("constant_empirical_acceleration_terms",
          &tep::constantEmpiricalAccelerationMagnitudes,
          py::arg("body"),
          py::arg("centralBody") );

}

}// namespace
}// namespace
}// namespace simulation
}// namespace tudatpy