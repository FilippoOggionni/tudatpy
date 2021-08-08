/*    Copyright (c) 2010-2021, Delft University of Technology
 *    All rights reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 */

#include "expose_propagator_setup.h"

#include <pybind11/chrono.h>
#include <pybind11/eigen.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>

namespace py = pybind11;
namespace tba = tudat::basic_astrodynamics;
namespace tss = tudat::simulation_setup;
namespace tp = tudat::propagators;
namespace tinterp = tudat::interpolators;
namespace te = tudat::ephemerides;
namespace tni = tudat::numerical_integrators;
namespace trf = tudat::reference_frames;
namespace tmrf = tudat::root_finders;


namespace tudatpy {
namespace simulation {
namespace propagation_setup {


    void expose_propagator_setup(py::module &m){

        // ENUMS
        py::enum_<tp::TranslationalPropagatorType>(m, "TranslationalPropagatorType")
                .value("undefined_translational_propagator",
                       tp::TranslationalPropagatorType::undefined_translational_propagator)
                .value("cowell",
                       tp::TranslationalPropagatorType::cowell)
                .value("encke",
                       tp::TranslationalPropagatorType::encke)
                .value("gauss_keplerian",
                       tp::TranslationalPropagatorType::gauss_keplerian)
                .value("gauss_modified_equinoctial",
                       tp::TranslationalPropagatorType::gauss_modified_equinoctial)
                .value("unified_state_model_quaternions",
                       tp::TranslationalPropagatorType::unified_state_model_quaternions)
                .value("unified_state_model_modified_rodrigues_parameters",
                       tp::TranslationalPropagatorType::unified_state_model_modified_rodrigues_parameters)
                .value("unified_state_model_exponential_map",
                       tp::unified_state_model_exponential_map)
                .export_values();

        py::enum_<tp::RotationalPropagatorType>(m, "RotationalPropagatorType")
                .value("undefined_rotational_propagator",
                       tp::RotationalPropagatorType::undefined_rotational_propagator)
                .value("quaternions",
                       tp::RotationalPropagatorType::quaternions)
                .value("modified_rodrigues_parameters",
                       tp::RotationalPropagatorType::modified_rodrigues_parameters)
                .value("exponential_map",
                       tp::RotationalPropagatorType::exponential_map)
                .export_values();

        // CLASSES
        py::class_<tp::DependentVariableSaveSettings,
                std::shared_ptr<tp::DependentVariableSaveSettings>>(m, "DependentVariableSaveSettings");
//                .def(py::init<
//                             const std::vector<std::shared_ptr<tp::SingleDependentVariableSaveSettings>>,
//                             const bool>(),
//                     py::arg("dependent_variables"),
//                     py::arg("print_dependent_variable_types") = true);

        py::class_<
        tp::PropagatorSettings<double>,
                std::shared_ptr<tp::PropagatorSettings<double>>>(m, "PropagatorSettings")
                .def("reset_initial_states", &tp::PropagatorSettings<double>::resetInitialStates,
                     py::arg("initial_states"));

        py::class_<
                tp::MultiArcPropagatorSettings<double>,
                std::shared_ptr<tp::MultiArcPropagatorSettings<double>>,
                tp::PropagatorSettings<double>>(m, "MultiArcPropagatorSettings");

        py::class_<
        tp::SingleArcPropagatorSettings<double>,
                std::shared_ptr<tp::SingleArcPropagatorSettings<double>>,
        tp::PropagatorSettings<double>>(m, "SingleArcPropagatorSettings")
                .def_property("termination_settings",
                              &tp::SingleArcPropagatorSettings<double>::getTerminationSettings,
                              &tp::SingleArcPropagatorSettings<double>::resetTerminationSettings);

        py::class_<
        tp::TranslationalStatePropagatorSettings<double>,
                std::shared_ptr<tp::TranslationalStatePropagatorSettings<double>>,
        tp::SingleArcPropagatorSettings<double>>(m, "TranslationalStatePropagatorSettings")
//                .def(// ctor 1
//                        py::init<
//                                const std::vector<std::string> &,
//                                const tba::AccelerationMap &,
//                                const std::vector<std::string> &,
//                                const Eigen::Matrix<double, Eigen::Dynamic, 1> &,
//                                const std::shared_ptr<tp::PropagationTerminationSettings>,
//                                const tp::TranslationalPropagatorType,
//                                const std::shared_ptr<tp::DependentVariableSaveSettings>,
//                                const double>(),
//                        py::arg("central_bodies"),
//                        py::arg("acceleration_models"),
//                        py::arg("bodies_to_integrate"),
//                        py::arg("initial_states"),
//                        py::arg("termination_settings"),
//                        py::arg("propagator") = tp::TranslationalPropagatorType::cowell,
//                        py::arg("output_variables") = std::shared_ptr<tp::DependentVariableSaveSettings>(),
//                        py::arg("print_interval") = TUDAT_NAN)
//                .def(// ctor 2
//                        py::init<const std::vector<std::string> &,
//                                const tss::SelectedAccelerationMap &,
//                                const std::vector<std::string> &,
//                                const Eigen::Matrix<double, Eigen::Dynamic, 1> &,
//                                const std::shared_ptr<tp::PropagationTerminationSettings>,
//                                const tp::TranslationalPropagatorType,
//                                const std::shared_ptr<tp::DependentVariableSaveSettings>,
//                                const double>(),
//                        py::arg("central_bodies"),
//                        py::arg("acceleration_settings"),
//                        py::arg("bodies_to_integrate"),
//                        py::arg("initial_states"),
//                        py::arg("termination_settings"),
//                        py::arg("propagator") = tp::cowell,
//                        py::arg("output_variables") = std::shared_ptr<tp::DependentVariableSaveSettings>(),
//                        py::arg("print_interval") = TUDAT_NAN)
//                .def(// ctor 3
//                        py::init<const std::vector<std::string> &,
//                                const tba::AccelerationMap &,
//                                const std::vector<std::string> &,
//                                const Eigen::Matrix<double, Eigen::Dynamic, 1> &,
//                                const double,
//                                const tp::TranslationalPropagatorType,
//                                const std::shared_ptr<tp::DependentVariableSaveSettings>,
//                                const double>(),
//                        py::arg("central_bodies"),
//                        py::arg("acceleration_models"),
//                        py::arg("bodies_to_integrate"),
//                        py::arg("initial_states"),
//                        py::arg("termination_time"),
//                        py::arg("propagator") = tp::cowell,
//                        py::arg("output_variables") = std::shared_ptr<tp::DependentVariableSaveSettings>(),
//                        py::arg("print_interval") = TUDAT_NAN)
//                .def(// ctor 4
//                        py::init<const std::vector<std::string> &,
//                                const tss::SelectedAccelerationMap &,
//                                const std::vector<std::string> &,
//                                const Eigen::Matrix<double, Eigen::Dynamic, 1> &,
//                                const double,
//                                const tp::TranslationalPropagatorType,
//                                const std::shared_ptr<tp::DependentVariableSaveSettings>,
//                                const double>(),
//                        py::arg("central_bodies"),
//                        py::arg("acceleration_settings"),
//                        py::arg("bodies_to_integrate"),
//                        py::arg("initial_states"),
//                        py::arg("termination_time"),
//                        py::arg("propagator") = tp::cowell,
//                        py::arg("output_variables") = std::shared_ptr<tp::DependentVariableSaveSettings>(),
//                        py::arg("print_interval") = TUDAT_NAN)
                .def("recreate_state_derivative_models", &tp::TranslationalStatePropagatorSettings<double>::resetIntegratedStateModels,
                     py::arg("bodies") )
                .def("get_propagated_state_size", &tp::TranslationalStatePropagatorSettings<double>::getPropagatedStateSize)
                .def("reset_and_recreate_acceleration_models", &tp::TranslationalStatePropagatorSettings<double>::resetAccelerationModelsMap,
                     py::arg("new_acceleration_settings"),
                     py::arg("bodies") )
                .def_property_readonly("acceleration_settings", &tp::TranslationalStatePropagatorSettings<double>::getAccelerationSettingsMap);


        py::class_<
            tp::MultiTypePropagatorSettings<double>,
            std::shared_ptr<tp::MultiTypePropagatorSettings<double>>,
            tp::SingleArcPropagatorSettings<double>>(m, "MultiTypePropagatorSettings")
                .def("reset_initial_states", &tp::MultiTypePropagatorSettings<double>::resetInitialStates,
                     py::arg("initial_states"))
                .def("recreate_state_derivative_models", &tp::MultiTypePropagatorSettings<double>::resetIntegratedStateModels,
                     py::arg("bodies") )
                .def("single_type_settings", &tp::MultiTypePropagatorSettings<double>::getSingleTypePropagatorSettings,
                     py::arg("state_type") )
                .def_property_readonly("propagator_settings_per_type", &tp::MultiTypePropagatorSettings<double>::getPropagatorSettingsMap);

        py::class_<
                tp::RotationalStatePropagatorSettings<double>,
                std::shared_ptr<tp::RotationalStatePropagatorSettings<double>>,
                tp::SingleArcPropagatorSettings<double>>(m, "RotationalStatePropagatorSettings");

        py::class_<
        tp::MassPropagatorSettings<double>,
                std::shared_ptr<tp::MassPropagatorSettings<double>>,
        tp::SingleArcPropagatorSettings<double>>(m, "MassPropagatorSettings");

        // FREE FUNCTIONS
        m.def("combine_initial_states",
              &tp::createCombinedInitialState<double>,
              py::arg("propagator_settings_per_type") );

        m.def("translational",
              py::overload_cast<
                      const std::vector< std::string >&,
                      const tba::AccelerationMap&,
                      const std::vector< std::string >&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const std::shared_ptr<tp::PropagationTerminationSettings>,
                      const tp::TranslationalPropagatorType,
                      const std::shared_ptr<tp::DependentVariableSaveSettings>,
                      const double>(&tp::translationalStatePropagatorSettings<double>),
              py::arg("central_bodies"),
              py::arg("acceleration_models"),
              py::arg("bodies_to_integrate"),
              py::arg("initial_states"),
              py::arg("termination_settings"),
              py::arg("propagator") = tp::cowell,
              py::arg("output_variables") = std::shared_ptr<tp::DependentVariableSaveSettings>(),
              py::arg("print_interval") = TUDAT_NAN);


        m.def("translational",
              py::overload_cast<
                      const std::vector< std::string >&,
                      const tba::AccelerationMap&,
                      const std::vector< std::string >&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const std::shared_ptr<tp::PropagationTerminationSettings>,
                      const tp::TranslationalPropagatorType,
                      const std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >&,
                      const double>(&tp::translationalStatePropagatorSettings<double>),
              py::arg("central_bodies"),
              py::arg("acceleration_models"),
              py::arg("bodies_to_integrate"),
              py::arg("initial_states"),
              py::arg("termination_settings"),
              py::arg("propagator") = tp::cowell,
              py::arg("output_variables") =  std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >(),
              py::arg("print_interval") = TUDAT_NAN);


        m.def("translational",
              py::overload_cast<
                      const std::vector< std::string >&,
                      const tba::AccelerationMap&,
                      const std::vector< std::string >&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const double,
                      const tp::TranslationalPropagatorType,
                      const std::shared_ptr<tp::DependentVariableSaveSettings>,
                      const double>(&tp::translationalStatePropagatorSettings<double>),
              py::arg("central_bodies"),
              py::arg("acceleration_models"),
              py::arg("bodies_to_integrate"),
              py::arg("initial_states"),
              py::arg("termination_time"),
              py::arg("propagator") = tp::cowell,
              py::arg("output_variables") = std::shared_ptr<tp::DependentVariableSaveSettings>(),
              py::arg("print_interval") = TUDAT_NAN);

        m.def("translational",
              py::overload_cast<
                      const std::vector< std::string >&,
                      const tba::AccelerationMap&,
                      const std::vector< std::string >&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const double,
                      const tp::TranslationalPropagatorType,
                      const std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >&,
                      const double>(&tp::translationalStatePropagatorSettings<double>),
              py::arg("central_bodies"),
              py::arg("acceleration_models"),
              py::arg("bodies_to_integrate"),
              py::arg("initial_states"),
              py::arg("termination_time"),
              py::arg("propagator") = tp::cowell,
              py::arg("output_variables") =  std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >(),
              py::arg("print_interval") = TUDAT_NAN);

        m.def("translational",
              py::overload_cast<
                      const std::vector< std::string >&,
                      const tss::SelectedAccelerationMap&,
                      const std::vector< std::string >&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const double,
                      const tp::TranslationalPropagatorType,
                      const std::shared_ptr<tp::DependentVariableSaveSettings>,
                      const double>(&tp::translationalStatePropagatorSettings<double>),
              py::arg("central_bodies"),
              py::arg("acceleration_settings"),
              py::arg("bodies_to_integrate"),
              py::arg("initial_states"),
              py::arg("termination_time"),
              py::arg("propagator") = tp::cowell,
              py::arg("output_variables") = std::shared_ptr<tp::DependentVariableSaveSettings>(),
              py::arg("print_interval") = TUDAT_NAN);

        m.def("translational",
              py::overload_cast<
                      const std::vector< std::string >&,
                      const tss::SelectedAccelerationMap&,
                      const std::vector< std::string >&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const std::shared_ptr<tp::PropagationTerminationSettings>,
                      const tp::TranslationalPropagatorType,
                      const std::shared_ptr<tp::DependentVariableSaveSettings>,
                      const double>(&tp::translationalStatePropagatorSettings<double>),
              py::arg("central_bodies"),
              py::arg("acceleration_settings"),
              py::arg("bodies_to_integrate"),
              py::arg("initial_states"),
              py::arg("termination_settings"),
              py::arg("propagator") = tp::cowell,
              py::arg("output_variables") = std::shared_ptr<tp::DependentVariableSaveSettings>(),
              py::arg("print_interval") = TUDAT_NAN);

        m.def("translational",
              py::overload_cast<
                      const std::vector< std::string >&,
                      const tss::SelectedAccelerationMap&,
                      const std::vector< std::string >&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const std::shared_ptr<tp::PropagationTerminationSettings>,
                      const tp::TranslationalPropagatorType,
                      const std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >&,
                      const double>(&tp::translationalStatePropagatorSettings<double>),
              py::arg("central_bodies"),
              py::arg("acceleration_settings"),
              py::arg("bodies_to_integrate"),
              py::arg("initial_states"),
              py::arg("termination_settings"),
              py::arg("propagator") = tp::cowell,
              py::arg("output_variables") = std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >(),
              py::arg("print_interval") = TUDAT_NAN);

        m.def("rotational",
              py::overload_cast<
                      const tba::TorqueModelMap&,
                      const std::vector< std::string >&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const std::shared_ptr<tp::PropagationTerminationSettings>,
                      const tp::RotationalPropagatorType,
                      const std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >,
                      const double>(&tp::rotationalStatePropagatorSettings<double>),
              py::arg("torque_models"),
              py::arg("bodies_to_integrate"),
              py::arg("initial_states"),
              py::arg("termination_settings"),
              py::arg("propagator") = tp::quaternions,
              py::arg("output_variables") = std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >(),
              py::arg("print_interval") = TUDAT_NAN);

        m.def("rotational",
              py::overload_cast<
                      const tss::SelectedTorqueMap&,
                      const std::vector< std::string >&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const std::shared_ptr<tp::PropagationTerminationSettings>,
                      const tp::RotationalPropagatorType,
                      const std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >,
                      const double>(&tp::rotationalStatePropagatorSettings<double>),
              py::arg("torque_settings"),
              py::arg("bodies_to_integrate"),
              py::arg("initial_states"),
              py::arg("termination_settings"),
              py::arg("propagator") = tp::quaternions,
              py::arg("output_variables") = std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >(),
              py::arg("print_interval") = TUDAT_NAN);


        m.def("mass",
              py::overload_cast<
                      const std::vector< std::string >,
                      const std::map< std::string, std::shared_ptr< tba::MassRateModel > >&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const std::shared_ptr< tp::PropagationTerminationSettings >,
                      const std::shared_ptr< tp::DependentVariableSaveSettings >,
                      const double >(&tp::massPropagatorSettings<double>),
              py::arg("bodies_with_mass_to_propagate"),
              py::arg("mass_rate_models"),
              py::arg("initial_body_masses"),
              py::arg("termination_settings"),
              py::arg("output_variables") = std::shared_ptr<tp::DependentVariableSaveSettings>(),
              py::arg("print_interval") = TUDAT_NAN);

        m.def("mass",
              py::overload_cast<
                      const std::vector< std::string >,
                      const std::map< std::string, std::vector< std::shared_ptr< tba::MassRateModel > > >&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const std::shared_ptr< tp::PropagationTerminationSettings >,
                      const std::shared_ptr< tp::DependentVariableSaveSettings >,
                      const double >(&tp::massPropagatorSettings<double>),
              py::arg("bodies_with_mass_to_propagate"),
              py::arg("mass_rate_models"),
              py::arg("initial_body_masses"),
              py::arg("termination_settings"),
              py::arg("output_variables") = std::shared_ptr<tp::DependentVariableSaveSettings>(),
              py::arg("print_interval") = TUDAT_NAN);

        m.def("mass",
              py::overload_cast<
                      const std::vector< std::string >,
                      const tss::SelectedMassRateModelMap&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const std::shared_ptr< tp::PropagationTerminationSettings >,
                      const std::shared_ptr< tp::DependentVariableSaveSettings >,
                      const double >(&tp::massPropagatorSettings<double>),
              py::arg("bodies_with_mass_to_propagate"),
              py::arg("mass_rate_settings"),
              py::arg("initial_body_masses"),
              py::arg("termination_settings"),
              py::arg("output_variables") = std::shared_ptr<tp::DependentVariableSaveSettings>(),
              py::arg("print_interval") = TUDAT_NAN);

        m.def("mass",
              py::overload_cast<
                      const std::vector< std::string >,
                      const std::map< std::string, std::vector< std::shared_ptr< tba::MassRateModel > > >&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const std::shared_ptr< tp::PropagationTerminationSettings >,
                      const std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >,
                      const double >(&tp::massPropagatorSettings<double>),
              py::arg("bodies_with_mass_to_propagate"),
              py::arg("mass_rate_models"),
              py::arg("initial_body_masses"),
              py::arg("termination_settings"),
              py::arg("output_variables") = std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >(),
              py::arg("print_interval") = TUDAT_NAN);


        m.def("mass",
              py::overload_cast<
                      const std::vector< std::string >,
                      const tss::SelectedMassRateModelMap&,
                      const Eigen::Matrix< double, Eigen::Dynamic, 1 >&,
                      const std::shared_ptr< tp::PropagationTerminationSettings >,
                      const std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >,
                      const double >(&tp::massPropagatorSettings<double>),
              py::arg("bodies_with_mass_to_propagate"),
              py::arg("mass_rate_settings"),
              py::arg("initial_body_masses"),
              py::arg("termination_settings"),
              py::arg("output_variables") = std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >(),
              py::arg("print_interval") = TUDAT_NAN);


        m.def("multitype",
              py::overload_cast<
                      const std::vector< std::shared_ptr< tp::SingleArcPropagatorSettings< double > > >,
        const std::shared_ptr< tp::PropagationTerminationSettings >,
        const std::shared_ptr< tp::DependentVariableSaveSettings >,
        const double >( &tp::multiTypePropagatorSettings<double> ),
                py::arg("propagator_settings_list"),
                py::arg("termination_settings"),
                py::arg("output_variables") = std::shared_ptr<tp::DependentVariableSaveSettings>( ),
                py::arg("print_interval") = TUDAT_NAN );

        m.def("multitype",
              py::overload_cast<
                      const std::vector< std::shared_ptr< tp::SingleArcPropagatorSettings< double > > >,
        const std::shared_ptr< tp::PropagationTerminationSettings >,
        const std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >,
        const double >( &tp::multiTypePropagatorSettings<double> ),
                py::arg("propagator_settings_list"),
                py::arg("termination_settings"),
                py::arg("output_variables") = std::vector< std::shared_ptr< tp::SingleDependentVariableSaveSettings > >( ),
                py::arg("print_interval") = TUDAT_NAN );

        m.def("multi_arc",
              &tp::multiArcPropagatorSettings<double>,
              py::arg("single_arc_settings"),
              py::arg("transfer_state_to_next_arc") = false );

        m.def("hybrid_arc",
              &tp::hybridArcPropagatorSettings<double>,
              py::arg("single_arc_settings"),
              py::arg("multi_arc_settings") );

        py::class_<tp::PropagationTerminationSettings,
                std::shared_ptr<tp::PropagationTerminationSettings>>
                PropagationTerminationSettings_(m, "PropagationTerminationSettings");

        py::class_<
                tp::PropagationDependentVariableTerminationSettings,
                std::shared_ptr<tp::PropagationDependentVariableTerminationSettings>,
                tp::PropagationTerminationSettings>(m, "PropagationDependentVariableTerminationSettings");
//                .def(py::init<
//                             const std::shared_ptr<tp::SingleDependentVariableSaveSettings>,
//                             const double,
//                             const bool,
//                             const bool,
//                             const std::shared_ptr<tudat::root_finders::RootFinderSettings>>(),
//                     py::arg("dependent_variadble_settings"),
//                     py::arg("limit_value"),
//                     py::arg("use_as_lower_limit"),
//                     py::arg("terminate_exactly_on_final_condition") = false,
//                     py::arg("termination_root_finder_settings") = nullptr);

        m.def("time_termination",
              &tp::propagationTimeTerminationSettings,
              py::arg("termination_time"),
              py::arg("terminate_exactly_on_final_condition") = false);

        m.def("cpu_time_termination",
              &tp::propagationCPUTimeTerminationSettings,
              py::arg("cpu_termination_time") );

        m.def("dependent_variable_termination",
              &tp::propagationDependentVariableTerminationSettings,
              py::arg("dependent_variable_settings"),
              py::arg("limit_value"),
              py::arg("use_as_lower_limit"),
              py::arg("terminate_exactly_on_final_condition") = false,
              py::arg("termination_root_finder_settings") = nullptr );

        m.def("custom_termination",
              &tp::popagationCustomTerminationSettings,
              py::arg("custom_condition"));


        m.def("hybrid_termination",
              &tp::propagationHybridTerminationSettings,
              py::arg("termination_settings"),
              py::arg("fulfill_single_condition") );
    }


}// namespace propagation_setup
}// namespace simulation
}// namespace tudatpy