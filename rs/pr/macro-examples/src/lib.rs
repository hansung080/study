// The `macro_use` attribute imports all macros declared in the `macros` module into the current scope.
// And all submodules can access the macros without paths.
#[macro_use] mod macros;
pub mod json;
mod net;