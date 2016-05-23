enum Depth {
    OnePly                 = 2,
    Depth0                 = 0,
    Depth1                 = 1,
    DepthQChecks           = -1 * OnePly,
    DepthQNoChecks         = -2 * OnePly,
    DepthQNoTT             = -3 * OnePly,
    DepthQRecaptures       = -5 * OnePly,
	DepthNone              = -127 * OnePly
};