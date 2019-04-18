namespace lcsc::constants {

/** A constant representing a small value of type T. */
template <typename T>
constexpr auto epsilon = (T)1e-5;

/** A constant representing pi with the precision of type T. */
template <typename T>
constexpr auto pi = (T)3.14159265359;

/** A constant representing sqrt(2) with the precision of type T. */
template <typename T>
constexpr auto sqrt2 = (T)1.41421356237;

} // namespace lcsc::constants
