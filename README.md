AMError
=======

## Changelog

- **0.2.7**
 - Xcode 7 compatibility and general modernization

- **0.2.6**
 - Build fixes 

- **0.2.5**
 - `localizedDescription` will now first use any explicitly set value, then
   fall back to strings table, and finally fall back to superclasses'
   implementation

- **0.2.4**
 - Accounting for NSError's default `localizedDescription` value
 - Allowing properties to be set to nil

- **0.2.3**
 - Setting `localizedDescription` to nil if not found in strings table

- **0.2.2**
 - Adding `strong` qualifier on properties

- **0.2.1**
 - Fixing bug in `AMErrorMakeWithInfo` macro

- **0.2.0**
 - Adding `AMErrorMakeWithInfo` macro

- **0.1.0**
   - Initial version
