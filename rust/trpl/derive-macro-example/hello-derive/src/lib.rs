extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, DeriveInput};

#[proc_macro_derive(HelloName)]
pub fn derive_hello_name(input: TokenStream) -> TokenStream {
    // let input = syn::parse(input).unwrap();
    let input = parse_macro_input!(input as DeriveInput);
    let typ = &input.ident;
    let expanded = quote! {
        impl hello::HelloName for #typ {
            fn hello_name() {
                println!("Hello, {}!", stringify!(#typ));
            }
        }
    };
    expanded.into()
}