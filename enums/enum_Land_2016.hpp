#ifndef EN_LAND_2016_HPP
#define EN_LAND_2016_HPP

enum E_CONSTANTS_T{
    dlambda_dt = 0,
    lambda = 1,
    Cai = 2,
    perm50 = 3,
    TRPN_n = 4,
    koff = 5,
    dr = 6,
    wfrac = 7,
    TOT_A = 8,
    ktm_unblock = 9,
    beta_1 = 10,
    beta_0 = 11,
    gamma_idx = 12,
    gamma_wu = 13,
    phi = 14,
    nperm = 15,
    //ca50 = 16,
    Tref = 17,
    nu = 18,
    mu = 19,
    k_ws = 20,
    k_uw = 21,
    par_k = 22,
    b = 23,
    eta_l = 24,
    eta_s = 25,
    land_a = 26,
    C = 27,
    Cd = 28,
    eta = 29,
};

enum E_ALGEBRAIC_T{
    Lfac = 0,
    cdw = 1,
    cds = 2,
    k_wu = 3,
    k_su = 4,
    A = 5,
    XU = 6,
    xb_ws = 7,
    xb_uw = 8,
    xb_wu = 9,
    xb_su = 10,
    gamma_rate = 11,
    xb_su_gamma = 12,
    gamma_rate_w = 13,
    xb_wu_gamma = 14,
    ca50 = 15,  // This appears to be both a CONSTANT and used like an ALGEBRAIC variable. Adjust based on your implementation needs.
    XSSS = 16,
    XWSS = 17,
    ktm_block = 18,
    Fd = 19,
    F1 = 20,
    Tp = 21,
    Ta = 22,
    land_T = 23,
};

enum E_STATES_T{
    XS = 0,
    XW = 1,
    TRPN = 2,
    TmBlocked = 3,
    ZETAS = 4,
    ZETAW = 5,
    dCd_dt = 6,

};


#endif