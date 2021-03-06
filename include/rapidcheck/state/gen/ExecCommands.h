#pragma once

namespace rc {
namespace state {
namespace gen {
namespace detail {

template <typename Cmd, typename... Cmds>
class ExecOneOf;

} // namespace detail

/// Given a type list of command types, returns a generator which randomly
/// generates one of them. The command will be generated by constructing
/// it either using a constructor taking the current state as as the only
/// parameter or using the default constructor if there is no such constructor.
/// Since the construction is done inside of a `gen::exec`, the command can
/// generate all of the needed values in its constructor using the
/// `Gen::operator*`. If the particular command is not valid for that state, it
/// can discard itself immediately using `RC_PRE` or `RC_DISCARD` in the
/// constructor so that another one may be tried. This can be used as the
/// generator function parameter of `check`.
template <typename Cmd, typename... Cmds>
RC_INTERNAL_DEPRECATED("Use execOneOfWithArgs instead")
Gen<std::shared_ptr<const typename Cmd::CommandType>> execOneOf(
    const typename Cmd::Model &state);

/// Similar to `execOneOf(Model)` but instead of returning a generator directly
/// it returns a callable which may be called with any number of arguments. When
/// this callable is called, it returns a generator that randomly generates one
/// of the commands by constructing it with the arguments to the callable or
/// using the default constructor if it cannot be constructed with those
/// arguments. Since the construction is done inside of a `gen::exec`, the
/// command can generate all of the needed values in its constructor using the
/// `Gen::operator*`. If the particular command is not valid for that state, it
/// can discard itself immediately using `RC_PRE` or `RC_DISCARD` in the
/// constructor so that another one may be tried. The returned callable can be
/// used as the generator function parameter of `check`.
template <typename Cmd, typename... Cmds>
detail::ExecOneOf<Cmd, Cmds...> execOneOfWithArgs();

} // namespace gen
} // namespace state
} // namespace rc

#include "ExecCommands.hpp"
