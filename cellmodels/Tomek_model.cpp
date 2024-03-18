/*
   There are a total of 223 entries in the algebraic variable array.
   There are a total of 43 entries in each of the rate and state variable arrays.
   There are a total of 163 entries in the constant variable array.
 */

#include "Tomek_model.hpp"
#include <cmath>
#include <cstdio>
#include <cstdlib>

/*
 * TIME is time in component environment (millisecond).
 * CONSTANTS[celltype] is celltype in component environment (dimensionless).
 * CONSTANTS[nao] is nao in component extracellular (millimolar).
 * CONSTANTS[cao] is cao in component extracellular (millimolar).
 * CONSTANTS[ko] is ko in component extracellular (millimolar).
 * CONSTANTS[clo] is clo in component extracellular (millimolar).
 * CONSTANTS[R] is R in component physical_constants (joule_per_kilomole_kelvin).
 * CONSTANTS[T] is T in component physical_constants (kelvin).
 * CONSTANTS[F] is F in component physical_constants (coulomb_per_mole).
 * CONSTANTS[zna] is zna in component physical_constants (dimensionless).
 * CONSTANTS[zca] is zca in component physical_constants (dimensionless).
 * CONSTANTS[zk] is zk in component physical_constants (dimensionless).
 * CONSTANTS[zcl] is zcl in component physical_constants (dimensionless).
 * CONSTANTS[L] is L in component cell_geometry (centimeter).
 * CONSTANTS[rad] is rad in component cell_geometry (centimeter).
 * CONSTANTS[vcell] is vcell in component cell_geometry (microliter).
 * CONSTANTS[Ageo] is Ageo in component cell_geometry (centimeter_squared).
 * CONSTANTS[Acap] is Acap in component cell_geometry (centimeter_squared).
 * CONSTANTS[vmyo] is vmyo in component cell_geometry (microliter).
 * CONSTANTS[vnsr] is vnsr in component cell_geometry (microliter).
 * CONSTANTS[vjsr] is vjsr in component cell_geometry (microliter).
 * CONSTANTS[vss] is vss in component cell_geometry (microliter).
 * STATES[v] is v in component membrane (millivolt).
 * ALGEBRAIC[vffrt] is vffrt in component membrane (coulomb_per_mole).
 * ALGEBRAIC[vfrt] is vfrt in component membrane (dimensionless).
 * ALGEBRAIC[INa] is INa in component INa (microA_per_microF).
 * ALGEBRAIC[INaL] is INaL in component INaL (microA_per_microF).
 * ALGEBRAIC[Ito] is Ito in component Ito (microA_per_microF).
 * ALGEBRAIC[ICaL] is ICaL in component ICaL (microA_per_microF).
 * ALGEBRAIC[ICaNa] is ICaNa in component ICaL (microA_per_microF).
 * ALGEBRAIC[ICaK] is ICaK in component ICaL (microA_per_microF).
 * ALGEBRAIC[IKr] is IKr in component IKr (microA_per_microF).
 * ALGEBRAIC[IKs] is IKs in component IKs (microA_per_microF).
 * ALGEBRAIC[IK1] is IK1 in component IK1 (microA_per_microF).
 * ALGEBRAIC[INaCa_i] is INaCa_i in component INaCa (microA_per_microF).
 * ALGEBRAIC[INaCa_ss] is INaCa_ss in component INaCa (microA_per_microF).
 * ALGEBRAIC[INaK] is INaK in component INaK (microA_per_microF).
 * ALGEBRAIC[INab] is INab in component INab (microA_per_microF).
 * ALGEBRAIC[IKb] is IKb in component IKb (microA_per_microF).
 * ALGEBRAIC[IpCa] is IpCa in component IpCa (microA_per_microF).
 * ALGEBRAIC[ICab] is ICab in component ICab (microA_per_microF).
 * ALGEBRAIC[IClCa] is IClCa in component ICl (microA_per_microF).
 * ALGEBRAIC[IClb] is IClb in component ICl (microA_per_microF).
 * ALGEBRAIC[I_katp] is I_katp in component I_katp (microA_per_microF).
 * ALGEBRAIC[Istim] is Istim in component membrane (microA_per_microF).
 * CONSTANTS[stim_start] is stim_start in component membrane (millisecond).
 * CONSTANTS[i_Stim_End] is i_Stim_End in component membrane (millisecond).
 * CONSTANTS[i_Stim_Amplitude] is i_Stim_Amplitude in component membrane (microA_per_microF).
 * CONSTANTS[BCL] is BCL in component membrane (millisecond).
 * CONSTANTS[i_Stim_PulseDuration] is i_Stim_PulseDuration in component membrane (millisecond).
 * CONSTANTS[KmCaMK] is KmCaMK in component CaMK (millimolar).
 * CONSTANTS[aCaMK] is aCaMK in component CaMK (per_millimolar_per_millisecond).
 * CONSTANTS[bCaMK] is bCaMK in component CaMK (per_millisecond).
 * CONSTANTS[CaMKo] is CaMKo in component CaMK (dimensionless).
 * CONSTANTS[KmCaM] is KmCaM in component CaMK (millimolar).
 * ALGEBRAIC[CaMKb] is CaMKb in component CaMK (millimolar).
 * ALGEBRAIC[CaMKa] is CaMKa in component CaMK (millimolar).
 * STATES[CaMKt] is CaMKt in component CaMK (millimolar).
 * STATES[cass] is cass in component intracellular_ions (millimolar).
 * CONSTANTS[cmdnmax_b] is cmdnmax_b in component intracellular_ions (millimolar).
 * CONSTANTS[cmdnmax] is cmdnmax in component intracellular_ions (millimolar).
 * CONSTANTS[kmcmdn] is kmcmdn in component intracellular_ions (millimolar).
 * CONSTANTS[trpnmax] is trpnmax in component intracellular_ions (millimolar).
 * CONSTANTS[kmtrpn] is kmtrpn in component intracellular_ions (millimolar).
 * CONSTANTS[BSRmax] is BSRmax in component intracellular_ions (millimolar).
 * CONSTANTS[KmBSR] is KmBSR in component intracellular_ions (millimolar).
 * CONSTANTS[BSLmax] is BSLmax in component intracellular_ions (millimolar).
 * CONSTANTS[KmBSL] is KmBSL in component intracellular_ions (millimolar).
 * CONSTANTS[csqnmax] is csqnmax in component intracellular_ions (millimolar).
 * CONSTANTS[kmcsqn] is kmcsqn in component intracellular_ions (millimolar).
 * STATES[nai] is nai in component intracellular_ions (millimolar).
 * STATES[nass] is nass in component intracellular_ions (millimolar).
 * STATES[ki] is ki in component intracellular_ions (millimolar).
 * STATES[kss] is kss in component intracellular_ions (millimolar).
 * STATES[cansr] is cansr in component intracellular_ions (millimolar).
 * STATES[cajsr] is cajsr in component intracellular_ions (millimolar).
 * STATES[cai] is cai in component intracellular_ions (millimolar).
 * CONSTANTS[cli] is cli in component intracellular_ions (millimolar).
 * ALGEBRAIC[ICaL_ss] is ICaL_ss in component ICaL (microA_per_microF).
 * ALGEBRAIC[ICaNa_ss] is ICaNa_ss in component ICaL (microA_per_microF).
 * ALGEBRAIC[ICaK_ss] is ICaK_ss in component ICaL (microA_per_microF).
 * ALGEBRAIC[ICaL_i] is ICaL_i in component ICaL (microA_per_microF).
 * ALGEBRAIC[ICaNa_i] is ICaNa_i in component ICaL (microA_per_microF).
 * ALGEBRAIC[ICaK_i] is ICaK_i in component ICaL (microA_per_microF).
 * ALGEBRAIC[JdiffNa] is JdiffNa in component diff (millimolar_per_millisecond).
 * ALGEBRAIC[Jdiff] is Jdiff in component diff (millimolar_per_millisecond).
 * ALGEBRAIC[Jup] is Jup in component SERCA (millimolar_per_millisecond).
 * ALGEBRAIC[JdiffK] is JdiffK in component diff (millimolar_per_millisecond).
 * ALGEBRAIC[Jrel] is Jrel in component ryr (millimolar_per_millisecond).
 * ALGEBRAIC[Jtr] is Jtr in component trans_flux (millimolar_per_millisecond).
 * ALGEBRAIC[Bcai] is Bcai in component intracellular_ions (dimensionless).
 * ALGEBRAIC[Bcajsr] is Bcajsr in component intracellular_ions (dimensionless).
 * ALGEBRAIC[Bcass] is Bcass in component intracellular_ions (dimensionless).
 * CONSTANTS[PKNa] is PKNa in component reversal_potentials (dimensionless).
 * ALGEBRAIC[ENa] is ENa in component reversal_potentials (millivolt).
 * ALGEBRAIC[EK] is EK in component reversal_potentials (millivolt).
 * ALGEBRAIC[EKs] is EKs in component reversal_potentials (millivolt).
 * CONSTANTS[ECl] is ECl in component reversal_potentials (millivolt).
 * CONSTANTS[gkatp] is gkatp in component I_katp (milliS_per_microF).
 * CONSTANTS[fkatp] is fkatp in component I_katp (dimensionless).
 * CONSTANTS[K_o_n] is K_o_n in component I_katp (millimolar).
 * CONSTANTS[A_atp] is A_atp in component I_katp (millimolar).
 * CONSTANTS[K_atp] is K_atp in component I_katp (millimolar).
 * CONSTANTS[akik] is akik in component I_katp (dimensionless).
 * CONSTANTS[bkik] is bkik in component I_katp (dimensionless).
 * ALGEBRAIC[mss] is mss in component INa (dimensionless).
 * ALGEBRAIC[tm] is tm in component INa (millisecond).
 * STATES[m] is m in component INa (dimensionless).
 * ALGEBRAIC[hss] is hss in component INa (dimensionless).
 * ALGEBRAIC[ah] is ah in component INa (dimensionless).
 * ALGEBRAIC[bh] is bh in component INa (dimensionless).
 * ALGEBRAIC[th] is th in component INa (millisecond).
 * STATES[h] is h in component INa (dimensionless).
 * ALGEBRAIC[jss] is jss in component INa (dimensionless).
 * ALGEBRAIC[aj] is aj in component INa (dimensionless).
 * ALGEBRAIC[bj] is bj in component INa (dimensionless).
 * ALGEBRAIC[tj] is tj in component INa (millisecond).
 * STATES[j] is j in component INa (dimensionless).
 * ALGEBRAIC[hssp] is hssp in component INa (dimensionless).
 * STATES[hp] is hp in component INa (dimensionless).
 * ALGEBRAIC[tjp] is tjp in component INa (millisecond).
 * STATES[jp] is jp in component INa (dimensionless).
 * ALGEBRAIC[fINap] is fINap in component INa (dimensionless).
 * CONSTANTS[GNa] is GNa in component INa (milliS_per_microF).
 * ALGEBRAIC[mLss] is mLss in component INaL (dimensionless).
 * ALGEBRAIC[tmL] is tmL in component INaL (millisecond).
 * STATES[mL] is mL in component INaL (dimensionless).
 * CONSTANTS[thL] is thL in component INaL (millisecond).
 * ALGEBRAIC[hLss] is hLss in component INaL (dimensionless).
 * STATES[hL] is hL in component INaL (dimensionless).
 * ALGEBRAIC[hLssp] is hLssp in component INaL (dimensionless).
 * CONSTANTS[thLp] is thLp in component INaL (millisecond).
 * STATES[hLp] is hLp in component INaL (dimensionless).
 * CONSTANTS[GNaL_b] is GNaL_b in component INaL (milliS_per_microF).
 * CONSTANTS[GNaL] is GNaL in component INaL (milliS_per_microF).
 * ALGEBRAIC[fINaLp] is fINaLp in component INaL (dimensionless).
 * CONSTANTS[Gto_b] is Gto_b in component Ito (milliS_per_microF).
 * ALGEBRAIC[ass] is ass in component Ito (dimensionless).
 * ALGEBRAIC[ta] is ta in component Ito (millisecond).
 * STATES[a] is a in component Ito (dimensionless).
 * CONSTANTS[EKshift] is EKshift in component Ito (millivolt).
 * ALGEBRAIC[iss] is iss in component Ito (dimensionless).
 * ALGEBRAIC[delta_epi] is delta_epi in component Ito (dimensionless).
 * ALGEBRAIC[tiF_b] is tiF_b in component Ito (millisecond).
 * ALGEBRAIC[tiS_b] is tiS_b in component Ito (millisecond).
 * ALGEBRAIC[tiF] is tiF in component Ito (millisecond).
 * ALGEBRAIC[tiS] is tiS in component Ito (millisecond).
 * ALGEBRAIC[AiF] is AiF in component Ito (dimensionless).
 * ALGEBRAIC[AiS] is AiS in component Ito (dimensionless).
 * STATES[iF] is iF in component Ito (dimensionless).
 * STATES[iS] is iS in component Ito (dimensionless).
 * ALGEBRAIC[i] is i in component Ito (dimensionless).
 * ALGEBRAIC[assp] is assp in component Ito (dimensionless).
 * STATES[ap] is ap in component Ito (dimensionless).
 * ALGEBRAIC[dti_develop] is dti_develop in component Ito (dimensionless).
 * ALGEBRAIC[dti_recover] is dti_recover in component Ito (dimensionless).
 * ALGEBRAIC[tiFp] is tiFp in component Ito (millisecond).
 * ALGEBRAIC[tiSp] is tiSp in component Ito (millisecond).
 * STATES[iFp] is iFp in component Ito (dimensionless).
 * STATES[iSp] is iSp in component Ito (dimensionless).
 * ALGEBRAIC[ip] is ip in component Ito (dimensionless).
 * CONSTANTS[Gto] is Gto in component Ito (milliS_per_microF).
 * ALGEBRAIC[fItop] is fItop in component Ito (dimensionless).
 * CONSTANTS[Kmn] is Kmn in component ICaL (millimolar).
 * CONSTANTS[k2n] is k2n in component ICaL (per_millisecond).
 * CONSTANTS[PCa_b] is PCa_b in component ICaL (dimensionless).
 * ALGEBRAIC[dss] is dss in component ICaL (dimensionless).
 * STATES[d] is d in component ICaL (dimensionless).
 * ALGEBRAIC[fss] is fss in component ICaL (dimensionless).
 * CONSTANTS[Aff] is Aff in component ICaL (dimensionless).
 * CONSTANTS[Afs] is Afs in component ICaL (dimensionless).
 * STATES[ff] is ff in component ICaL (dimensionless).
 * STATES[fs] is fs in component ICaL (dimensionless).
 * ALGEBRAIC[f] is f in component ICaL (dimensionless).
 * ALGEBRAIC[fcass] is fcass in component ICaL (dimensionless).
 * ALGEBRAIC[jcass] is jcass in component ICaL (dimensionless).
 * ALGEBRAIC[Afcaf] is Afcaf in component ICaL (dimensionless).
 * ALGEBRAIC[Afcas] is Afcas in component ICaL (dimensionless).
 * STATES[fcaf] is fcaf in component ICaL (dimensionless).
 * STATES[fcas] is fcas in component ICaL (dimensionless).
 * ALGEBRAIC[fca] is fca in component ICaL (dimensionless).
 * STATES[jca] is jca in component ICaL (dimensionless).
 * STATES[ffp] is ffp in component ICaL (dimensionless).
 * ALGEBRAIC[fp] is fp in component ICaL (dimensionless).
 * STATES[fcafp] is fcafp in component ICaL (dimensionless).
 * ALGEBRAIC[fcap] is fcap in component ICaL (dimensionless).
 * ALGEBRAIC[km2n] is km2n in component ICaL (per_millisecond).
 * ALGEBRAIC[anca_ss] is anca_ss in component ICaL (dimensionless).
 * STATES[nca_ss] is nca_ss in component ICaL (dimensionless).
 * ALGEBRAIC[anca_i] is anca_i in component ICaL (dimensionless).
 * STATES[nca_i] is nca_i in component ICaL (dimensionless).
 * ALGEBRAIC[PhiCaL_ss] is PhiCaL_ss in component ICaL (dimensionless).
 * ALGEBRAIC[PhiCaNa_ss] is PhiCaNa_ss in component ICaL (dimensionless).
 * ALGEBRAIC[PhiCaK_ss] is PhiCaK_ss in component ICaL (dimensionless).
 * ALGEBRAIC[PhiCaL_i] is PhiCaL_i in component ICaL (dimensionless).
 * ALGEBRAIC[PhiCaNa_i] is PhiCaNa_i in component ICaL (dimensionless).
 * ALGEBRAIC[PhiCaK_i] is PhiCaK_i in component ICaL (dimensionless).
 * CONSTANTS[PCa] is PCa in component ICaL (dimensionless).
 * CONSTANTS[PCap] is PCap in component ICaL (dimensionless).
 * CONSTANTS[PCaNa] is PCaNa in component ICaL (dimensionless).
 * CONSTANTS[PCaK] is PCaK in component ICaL (dimensionless).
 * CONSTANTS[PCaNap] is PCaNap in component ICaL (dimensionless).
 * CONSTANTS[PCaKp] is PCaKp in component ICaL (dimensionless).
 * ALGEBRAIC[fICaLp] is fICaLp in component ICaL (dimensionless).
 * ALGEBRAIC[td] is td in component ICaL (millisecond).
 * ALGEBRAIC[tff] is tff in component ICaL (millisecond).
 * ALGEBRAIC[tfs] is tfs in component ICaL (millisecond).
 * ALGEBRAIC[tfcaf] is tfcaf in component ICaL (millisecond).
 * ALGEBRAIC[tfcas] is tfcas in component ICaL (millisecond).
 * CONSTANTS[tjca] is tjca in component ICaL (millisecond).
 * ALGEBRAIC[tffp] is tffp in component ICaL (millisecond).
 * ALGEBRAIC[tfcafp] is tfcafp in component ICaL (millisecond).
 * CONSTANTS[vShift] is vShift in component ICaL (millivolt).
 * CONSTANTS[offset] is offset in component ICaL (millisecond).
 * CONSTANTS[Io] is Io in component ICaL (dimensionless).
 * ALGEBRAIC[Iss] is Iss in component ICaL (dimensionless).
 * ALGEBRAIC[Ii] is Ii in component ICaL (dimensionless).
 * CONSTANTS[dielConstant] is dielConstant in component ICaL (per_kelvin).
 * CONSTANTS[constA] is constA in component ICaL (dimensionless).
 * CONSTANTS[gamma_cao] is gamma_cao in component ICaL (dimensionless).
 * ALGEBRAIC[gamma_cass] is gamma_cass in component ICaL (dimensionless).
 * ALGEBRAIC[gamma_cai] is gamma_cai in component ICaL (dimensionless).
 * CONSTANTS[gamma_nao] is gamma_nao in component ICaL (dimensionless).
 * ALGEBRAIC[gamma_nass] is gamma_nass in component ICaL (dimensionless).
 * ALGEBRAIC[gamma_nai] is gamma_nai in component ICaL (dimensionless).
 * CONSTANTS[gamma_ko] is gamma_ko in component ICaL (dimensionless).
 * ALGEBRAIC[gamma_kss] is gamma_kss in component ICaL (dimensionless).
 * ALGEBRAIC[gamma_ki] is gamma_ki in component ICaL (dimensionless).
 * CONSTANTS[ICaL_fractionSS] is ICaL_fractionSS in component ICaL (dimensionless).
 * CONSTANTS[GKr_b] is GKr_b in component IKr (milliS_per_microF).
 * STATES[C1] is C1 in component IKr (dimensionless).
 * STATES[C2] is C2 in component IKr (dimensionless).
 * STATES[C3] is C3 in component IKr (dimensionless).
 * STATES[I] is I in component IKr (dimensionless).
 * STATES[O] is O in component IKr (dimensionless).
 * ALGEBRAIC[alpha] is alpha in component IKr (per_millisecond).
 * ALGEBRAIC[beta] is beta in component IKr (per_millisecond).
 * CONSTANTS[alpha_1] is alpha_1 in component IKr (per_millisecond).
 * CONSTANTS[beta_1] is beta_1 in component IKr (per_millisecond).
 * ALGEBRAIC[alpha_2] is alpha_2 in component IKr (per_millisecond).
 * ALGEBRAIC[beta_2] is beta_2 in component IKr (per_millisecond).
 * ALGEBRAIC[alpha_i] is alpha_i in component IKr (per_millisecond).
 * ALGEBRAIC[beta_i] is beta_i in component IKr (per_millisecond).
 * ALGEBRAIC[alpha_C2ToI] is alpha_C2ToI in component IKr (per_millisecond).
 * ALGEBRAIC[beta_ItoC2] is beta_ItoC2 in component IKr (per_millisecond).
 * CONSTANTS[GKr] is GKr in component IKr (milliS_per_microF).
 * CONSTANTS[GKs_b] is GKs_b in component IKs (milliS_per_microF).
 * CONSTANTS[GKs] is GKs in component IKs (milliS_per_microF).
 * ALGEBRAIC[xs1ss] is xs1ss in component IKs (dimensionless).
 * ALGEBRAIC[xs2ss] is xs2ss in component IKs (dimensionless).
 * ALGEBRAIC[txs1] is txs1 in component IKs (millisecond).
 * STATES[xs1] is xs1 in component IKs (dimensionless).
 * STATES[xs2] is xs2 in component IKs (dimensionless).
 * ALGEBRAIC[KsCa] is KsCa in component IKs (dimensionless).
 * ALGEBRAIC[txs2] is txs2 in component IKs (millisecond).
 * CONSTANTS[GK1] is GK1 in component IK1 (milliS_per_microF).
 * CONSTANTS[GK1_b] is GK1_b in component IK1 (milliS_per_microF).
 * ALGEBRAIC[aK1] is aK1 in component IK1 (dimensionless).
 * ALGEBRAIC[bK1] is bK1 in component IK1 (dimensionless).
 * ALGEBRAIC[K1ss] is K1ss in component IK1 (dimensionless).
 * CONSTANTS[INaCa_fractionSS] is INaCa_fractionSS in component INaCa (dimensionless).
 * CONSTANTS[kna1] is kna1 in component INaCa (per_millisecond).
 * CONSTANTS[kna2] is kna2 in component INaCa (per_millisecond).
 * CONSTANTS[kna3] is kna3 in component INaCa (per_millisecond).
 * CONSTANTS[kasymm] is kasymm in component INaCa (dimensionless).
 * CONSTANTS[wna] is wna in component INaCa (dimensionless).
 * CONSTANTS[wca] is wca in component INaCa (dimensionless).
 * CONSTANTS[wnaca] is wnaca in component INaCa (dimensionless).
 * CONSTANTS[kcaon] is kcaon in component INaCa (per_millisecond).
 * CONSTANTS[kcaoff] is kcaoff in component INaCa (per_millisecond).
 * CONSTANTS[qna] is qna in component INaCa (dimensionless).
 * CONSTANTS[qca] is qca in component INaCa (dimensionless).
 * ALGEBRAIC[hna] is hna in component INaCa (dimensionless).
 * ALGEBRAIC[hca] is hca in component INaCa (dimensionless).
 * CONSTANTS[KmCaAct] is KmCaAct in component INaCa (millimolar).
 * CONSTANTS[Gncx_b] is Gncx_b in component INaCa (milliS_per_microF).
 * CONSTANTS[Gncx] is Gncx in component INaCa (milliS_per_microF).
 * ALGEBRAIC[h1_i] is h1_i in component INaCa (dimensionless).
 * ALGEBRAIC[h2_i] is h2_i in component INaCa (dimensionless).
 * ALGEBRAIC[h3_i] is h3_i in component INaCa (dimensionless).
 * ALGEBRAIC[h4_i] is h4_i in component INaCa (dimensionless).
 * ALGEBRAIC[h5_i] is h5_i in component INaCa (dimensionless).
 * ALGEBRAIC[h6_i] is h6_i in component INaCa (dimensionless).
 * ALGEBRAIC[h7_i] is h7_i in component INaCa (dimensionless).
 * ALGEBRAIC[h8_i] is h8_i in component INaCa (dimensionless).
 * ALGEBRAIC[h9_i] is h9_i in component INaCa (dimensionless).
 * CONSTANTS[h10_i] is h10_i in component INaCa (dimensionless).
 * CONSTANTS[h11_i] is h11_i in component INaCa (dimensionless).
 * CONSTANTS[h12_i] is h12_i in component INaCa (dimensionless).
 * CONSTANTS[k1_i] is k1_i in component INaCa (dimensionless).
 * CONSTANTS[k2_i] is k2_i in component INaCa (dimensionless).
 * ALGEBRAIC[k3p_i] is k3p_i in component INaCa (dimensionless).
 * ALGEBRAIC[k3pp_i] is k3pp_i in component INaCa (dimensionless).
 * ALGEBRAIC[k3_i] is k3_i in component INaCa (dimensionless).
 * ALGEBRAIC[k4_i] is k4_i in component INaCa (dimensionless).
 * ALGEBRAIC[k4p_i] is k4p_i in component INaCa (dimensionless).
 * ALGEBRAIC[k4pp_i] is k4pp_i in component INaCa (dimensionless).
 * CONSTANTS[k5_i] is k5_i in component INaCa (dimensionless).
 * ALGEBRAIC[k6_i] is k6_i in component INaCa (dimensionless).
 * ALGEBRAIC[k7_i] is k7_i in component INaCa (dimensionless).
 * ALGEBRAIC[k8_i] is k8_i in component INaCa (dimensionless).
 * ALGEBRAIC[x1_i] is x1_i in component INaCa (dimensionless).
 * ALGEBRAIC[x2_i] is x2_i in component INaCa (dimensionless).
 * ALGEBRAIC[x3_i] is x3_i in component INaCa (dimensionless).
 * ALGEBRAIC[x4_i] is x4_i in component INaCa (dimensionless).
 * ALGEBRAIC[E1_i] is E1_i in component INaCa (dimensionless).
 * ALGEBRAIC[E2_i] is E2_i in component INaCa (dimensionless).
 * ALGEBRAIC[E3_i] is E3_i in component INaCa (dimensionless).
 * ALGEBRAIC[E4_i] is E4_i in component INaCa (dimensionless).
 * ALGEBRAIC[allo_i] is allo_i in component INaCa (dimensionless).
 * ALGEBRAIC[JncxNa_i] is JncxNa_i in component INaCa (millimolar_per_millisecond).
 * ALGEBRAIC[JncxCa_i] is JncxCa_i in component INaCa (millimolar_per_millisecond).
 * ALGEBRAIC[h1_ss] is h1_ss in component INaCa (dimensionless).
 * ALGEBRAIC[h2_ss] is h2_ss in component INaCa (dimensionless).
 * ALGEBRAIC[h3_ss] is h3_ss in component INaCa (dimensionless).
 * ALGEBRAIC[h4_ss] is h4_ss in component INaCa (dimensionless).
 * ALGEBRAIC[h5_ss] is h5_ss in component INaCa (dimensionless).
 * ALGEBRAIC[h6_ss] is h6_ss in component INaCa (dimensionless).
 * ALGEBRAIC[h7_ss] is h7_ss in component INaCa (dimensionless).
 * ALGEBRAIC[h8_ss] is h8_ss in component INaCa (dimensionless).
 * ALGEBRAIC[h9_ss] is h9_ss in component INaCa (dimensionless).
 * CONSTANTS[h10_ss] is h10_ss in component INaCa (dimensionless).
 * CONSTANTS[h11_ss] is h11_ss in component INaCa (dimensionless).
 * CONSTANTS[h12_ss] is h12_ss in component INaCa (dimensionless).
 * CONSTANTS[k1_ss] is k1_ss in component INaCa (dimensionless).
 * CONSTANTS[k2_ss] is k2_ss in component INaCa (dimensionless).
 * ALGEBRAIC[k3p_ss] is k3p_ss in component INaCa (dimensionless).
 * ALGEBRAIC[k3pp_ss] is k3pp_ss in component INaCa (dimensionless).
 * ALGEBRAIC[k3_ss] is k3_ss in component INaCa (dimensionless).
 * ALGEBRAIC[k4_ss] is k4_ss in component INaCa (dimensionless).
 * ALGEBRAIC[k4p_ss] is k4p_ss in component INaCa (dimensionless).
 * ALGEBRAIC[k4pp_ss] is k4pp_ss in component INaCa (dimensionless).
 * CONSTANTS[k5_ss] is k5_ss in component INaCa (dimensionless).
 * ALGEBRAIC[k6_ss] is k6_ss in component INaCa (dimensionless).
 * ALGEBRAIC[k7_ss] is k7_ss in component INaCa (dimensionless).
 * ALGEBRAIC[k8_ss] is k8_ss in component INaCa (dimensionless).
 * ALGEBRAIC[x1_ss] is x1_ss in component INaCa (dimensionless).
 * ALGEBRAIC[x2_ss] is x2_ss in component INaCa (dimensionless).
 * ALGEBRAIC[x3_ss] is x3_ss in component INaCa (dimensionless).
 * ALGEBRAIC[x4_ss] is x4_ss in component INaCa (dimensionless).
 * ALGEBRAIC[E1_ss] is E1_ss in component INaCa (dimensionless).
 * ALGEBRAIC[E2_ss] is E2_ss in component INaCa (dimensionless).
 * ALGEBRAIC[E3_ss] is E3_ss in component INaCa (dimensionless).
 * ALGEBRAIC[E4_ss] is E4_ss in component INaCa (dimensionless).
 * ALGEBRAIC[allo_ss] is allo_ss in component INaCa (dimensionless).
 * ALGEBRAIC[JncxNa_ss] is JncxNa_ss in component INaCa (millimolar_per_millisecond).
 * ALGEBRAIC[JncxCa_ss] is JncxCa_ss in component INaCa (millimolar_per_millisecond).
 * CONSTANTS[k1p] is k1p in component INaK (per_millisecond).
 * CONSTANTS[k1m] is k1m in component INaK (per_millisecond).
 * CONSTANTS[k2p] is k2p in component INaK (per_millisecond).
 * CONSTANTS[k2m] is k2m in component INaK (per_millisecond).
 * CONSTANTS[k3p] is k3p in component INaK (per_millisecond).
 * CONSTANTS[k3m] is k3m in component INaK (per_millisecond).
 * CONSTANTS[k4p] is k4p in component INaK (per_millisecond).
 * CONSTANTS[k4m] is k4m in component INaK (per_millisecond).
 * CONSTANTS[Knai0] is Knai0 in component INaK (millimolar).
 * CONSTANTS[Knao0] is Knao0 in component INaK (millimolar).
 * CONSTANTS[delta] is delta in component INaK (millivolt).
 * CONSTANTS[Kki] is Kki in component INaK (per_millisecond).
 * CONSTANTS[Kko] is Kko in component INaK (per_millisecond).
 * CONSTANTS[MgADP] is MgADP in component INaK (millimolar).
 * CONSTANTS[MgATP] is MgATP in component INaK (millimolar).
 * CONSTANTS[Kmgatp] is Kmgatp in component INaK (millimolar).
 * CONSTANTS[H] is H in component INaK (millimolar).
 * CONSTANTS[eP] is eP in component INaK (dimensionless).
 * CONSTANTS[Khp] is Khp in component INaK (millimolar).
 * CONSTANTS[Knap] is Knap in component INaK (millimolar).
 * CONSTANTS[Kxkur] is Kxkur in component INaK (millimolar).
 * CONSTANTS[Pnak_b] is Pnak_b in component INaK (milliS_per_microF).
 * CONSTANTS[Pnak] is Pnak in component INaK (milliS_per_microF).
 * ALGEBRAIC[Knai] is Knai in component INaK (millimolar).
 * ALGEBRAIC[Knao] is Knao in component INaK (millimolar).
 * ALGEBRAIC[P] is P in component INaK (dimensionless).
 * ALGEBRAIC[a1] is a1 in component INaK (dimensionless).
 * CONSTANTS[b1] is b1 in component INaK (dimensionless).
 * CONSTANTS[a2] is a2 in component INaK (dimensionless).
 * ALGEBRAIC[b2] is b2 in component INaK (dimensionless).
 * ALGEBRAIC[a3] is a3 in component INaK (dimensionless).
 * ALGEBRAIC[b3] is b3 in component INaK (dimensionless).
 * CONSTANTS[a4] is a4 in component INaK (dimensionless).
 * ALGEBRAIC[b4] is b4 in component INaK (dimensionless).
 * ALGEBRAIC[x1] is x1 in component INaK (dimensionless).
 * ALGEBRAIC[x2] is x2 in component INaK (dimensionless).
 * ALGEBRAIC[x3] is x3 in component INaK (dimensionless).
 * ALGEBRAIC[x4] is x4 in component INaK (dimensionless).
 * ALGEBRAIC[E1] is E1 in component INaK (dimensionless).
 * ALGEBRAIC[E2] is E2 in component INaK (dimensionless).
 * ALGEBRAIC[E3] is E3 in component INaK (dimensionless).
 * ALGEBRAIC[E4] is E4 in component INaK (dimensionless).
 * ALGEBRAIC[JnakNa] is JnakNa in component INaK (millimolar_per_millisecond).
 * ALGEBRAIC[JnakK] is JnakK in component INaK (millimolar_per_millisecond).
 * ALGEBRAIC[xkb] is xkb in component IKb (dimensionless).
 * CONSTANTS[GKb_b] is GKb_b in component IKb (milliS_per_microF).
 * CONSTANTS[GKb] is GKb in component IKb (milliS_per_microF).
 * CONSTANTS[PNab] is PNab in component INab (milliS_per_microF).
 * CONSTANTS[PCab] is PCab in component ICab (milliS_per_microF).
 * CONSTANTS[GpCa] is GpCa in component IpCa (milliS_per_microF).
 * CONSTANTS[KmCap] is KmCap in component IpCa (millimolar).
 * CONSTANTS[GClCa] is GClCa in component ICl (milliS_per_microF).
 * CONSTANTS[GClb] is GClb in component ICl (milliS_per_microF).
 * CONSTANTS[KdClCa] is KdClCa in component ICl (millimolar).
 * CONSTANTS[Fjunc] is Fjunc in component ICl (dimensionless).
 * ALGEBRAIC[IClCa_junc] is IClCa_junc in component ICl (microA_per_microF).
 * ALGEBRAIC[IClCa_sl] is IClCa_sl in component ICl (microA_per_microF).
 * CONSTANTS[tauNa] is tauNa in component diff (millisecond).
 * CONSTANTS[tauK] is tauK in component diff (millisecond).
 * CONSTANTS[tauCa] is tauCa in component diff (millisecond).
 * CONSTANTS[bt] is bt in component ryr (millisecond).
 * CONSTANTS[a_rel] is a_rel in component ryr (millimolar_per_millisecond).
 * ALGEBRAIC[Jrel_inf_b] is Jrel_inf_b in component ryr (millimolar_per_millisecond).
 * ALGEBRAIC[Jrel_inf] is Jrel_inf in component ryr (millimolar_per_millisecond).
 * ALGEBRAIC[tau_rel_b] is tau_rel_b in component ryr (millisecond).
 * ALGEBRAIC[tau_rel] is tau_rel in component ryr (millisecond).
 * STATES[Jrel_np] is Jrel_np in component ryr (millimolar_per_millisecond).
 * CONSTANTS[btp] is btp in component ryr (millisecond).
 * CONSTANTS[a_relp] is a_relp in component ryr (millimolar_per_millisecond).
 * ALGEBRAIC[Jrel_infp_b] is Jrel_infp_b in component ryr (millimolar_per_millisecond).
 * ALGEBRAIC[Jrel_infp] is Jrel_infp in component ryr (millimolar_per_millisecond).
 * ALGEBRAIC[tau_relp_b] is tau_relp_b in component ryr (millisecond).
 * ALGEBRAIC[tau_relp] is tau_relp in component ryr (millisecond).
 * STATES[Jrel_p] is Jrel_p in component ryr (millimolar_per_millisecond).
 * CONSTANTS[cajsr_half] is cajsr_half in component ryr (millimolar).
 * ALGEBRAIC[fJrelp] is fJrelp in component ryr (dimensionless).
 * CONSTANTS[Jrel_b] is Jrel_b in component ryr (dimensionless).
 * CONSTANTS[upScale] is upScale in component SERCA (dimensionless).
 * ALGEBRAIC[Jupnp] is Jupnp in component SERCA (millimolar_per_millisecond).
 * ALGEBRAIC[Jupp] is Jupp in component SERCA (millimolar_per_millisecond).
 * ALGEBRAIC[fJupp] is fJupp in component SERCA (dimensionless).
 * ALGEBRAIC[Jleak] is Jleak in component SERCA (millimolar_per_millisecond).
 * CONSTANTS[Jup_b] is Jup_b in component SERCA (dimensionless).
 * RATES[v] is d/dt v in component membrane (millivolt).
 * RATES[CaMKt] is d/dt CaMKt in component CaMK (millimolar).
 * RATES[nai] is d/dt nai in component intracellular_ions (millimolar).
 * RATES[nass] is d/dt nass in component intracellular_ions (millimolar).
 * RATES[ki] is d/dt ki in component intracellular_ions (millimolar).
 * RATES[kss] is d/dt kss in component intracellular_ions (millimolar).
 * RATES[cai] is d/dt cai in component intracellular_ions (millimolar).
 * RATES[cass] is d/dt cass in component intracellular_ions (millimolar).
 * RATES[cansr] is d/dt cansr in component intracellular_ions (millimolar).
 * RATES[cajsr] is d/dt cajsr in component intracellular_ions (millimolar).
 * RATES[m] is d/dt m in component INa (dimensionless).
 * RATES[h] is d/dt h in component INa (dimensionless).
 * RATES[j] is d/dt j in component INa (dimensionless).
 * RATES[hp] is d/dt hp in component INa (dimensionless).
 * RATES[jp] is d/dt jp in component INa (dimensionless).
 * RATES[mL] is d/dt mL in component INaL (dimensionless).
 * RATES[hL] is d/dt hL in component INaL (dimensionless).
 * RATES[hLp] is d/dt hLp in component INaL (dimensionless).
 * RATES[a] is d/dt a in component Ito (dimensionless).
 * RATES[iF] is d/dt iF in component Ito (dimensionless).
 * RATES[iS] is d/dt iS in component Ito (dimensionless).
 * RATES[ap] is d/dt ap in component Ito (dimensionless).
 * RATES[iFp] is d/dt iFp in component Ito (dimensionless).
 * RATES[iSp] is d/dt iSp in component Ito (dimensionless).
 * RATES[d] is d/dt d in component ICaL (dimensionless).
 * RATES[ff] is d/dt ff in component ICaL (dimensionless).
 * RATES[fs] is d/dt fs in component ICaL (dimensionless).
 * RATES[fcaf] is d/dt fcaf in component ICaL (dimensionless).
 * RATES[fcas] is d/dt fcas in component ICaL (dimensionless).
 * RATES[jca] is d/dt jca in component ICaL (dimensionless).
 * RATES[ffp] is d/dt ffp in component ICaL (dimensionless).
 * RATES[fcafp] is d/dt fcafp in component ICaL (dimensionless).
 * RATES[nca_ss] is d/dt nca_ss in component ICaL (dimensionless).
 * RATES[nca_i] is d/dt nca_i in component ICaL (dimensionless).
 * RATES[C3] is d/dt C3 in component IKr (dimensionless).
 * RATES[C2] is d/dt C2 in component IKr (dimensionless).
 * RATES[C1] is d/dt C1 in component IKr (dimensionless).
 * RATES[O] is d/dt O in component IKr (dimensionless).
 * RATES[I] is d/dt I in component IKr (dimensionless).
 * RATES[xs1] is d/dt xs1 in component IKs (dimensionless).
 * RATES[xs2] is d/dt xs2 in component IKs (dimensionless).
 * RATES[Jrel_np] is d/dt Jrel_np in component ryr (millimolar_per_millisecond).
 * RATES[Jrel_p] is d/dt Jrel_p in component ryr (millimolar_per_millisecond).
 */


Tomek_model::Tomek_model()
{
algebraic_size = 223;
constants_size = 163;
states_size = 43;
ALGEBRAIC = new double[algebraic_size];
CONSTANTS = new double[constants_size];
RATES = new double[states_size];
STATES = new double[states_size];
}

Tomek_model::~Tomek_model()
{
delete []ALGEBRAIC;
delete []CONSTANTS;
delete []RATES;
delete []STATES;
}

void Tomek_model::initConsts()
{
CONSTANTS[nao] = 140.0;
CONSTANTS[cao] = 1.8;
CONSTANTS[ko] = 5.0;
CONSTANTS[clo] = 150.0;
CONSTANTS[R] = 8314;
CONSTANTS[T] = 310;
CONSTANTS[F] = 96485;
CONSTANTS[zna] = 1;
CONSTANTS[zca] = 2;
CONSTANTS[zk] = 1;
CONSTANTS[zcl] = -1;
CONSTANTS[L] = 0.01;
CONSTANTS[rad] = 0.0011;
STATES[v] = (CONSTANTS[celltype]==1.00000 ?  -89.14 : CONSTANTS[celltype]==2.00000 ?  -89.1704 : -88.7638);
CONSTANTS[stim_start] = 10;
CONSTANTS[i_Stim_End] = 100000000000000000;
CONSTANTS[i_Stim_Amplitude] = -53;
CONSTANTS[BCL] = 1000;
CONSTANTS[i_Stim_PulseDuration] = 1.0;
CONSTANTS[KmCaMK] = 0.15;
CONSTANTS[aCaMK] = 0.05;
CONSTANTS[bCaMK] = 0.00068;
CONSTANTS[CaMKo] = 0.05;
CONSTANTS[KmCaM] = 0.0015;
STATES[CaMKt] = (CONSTANTS[celltype]==1.00000 ? 0.0129 : CONSTANTS[celltype]==2.00000 ? 0.0192 : 0.0111);
STATES[cass] = (CONSTANTS[celltype]==1.00000 ? 5.77E-05 : CONSTANTS[celltype]==2.00000 ? 6.58E-05 : 7.0305e-5);
CONSTANTS[cmdnmax_b] = 0.05;
CONSTANTS[kmcmdn] = 0.00238;
CONSTANTS[trpnmax] = 0.07;
CONSTANTS[kmtrpn] = 0.0005;
CONSTANTS[BSRmax] = 0.047;
CONSTANTS[KmBSR] = 0.00087;
CONSTANTS[BSLmax] = 1.124;
CONSTANTS[KmBSL] = 0.0087;
CONSTANTS[csqnmax] = 10;
CONSTANTS[kmcsqn] = 0.8;
STATES[nai] = (CONSTANTS[celltype]==1.00000 ? 12.1025 : CONSTANTS[celltype]==2.00000 ? 15.0038 : 12.1025);
STATES[nass] = (CONSTANTS[celltype]==1.00000 ? 12.8366 : CONSTANTS[celltype]==2.00000 ? 15.0043 : 12.1029);
STATES[ki] = (CONSTANTS[celltype]==1.00000 ? 142.6951 : CONSTANTS[celltype]==2.00000 ? 143.0403 : 142.3002);
STATES[kss] = (CONSTANTS[celltype]==1.00000 ? 142.6951 : CONSTANTS[celltype]==2.00000 ? 143.0402 : 142.3002);
STATES[cansr] = (CONSTANTS[celltype]==1.00000 ? 1.8119 : CONSTANTS[celltype]==2.00000 ? 1.9557 : 1.5211);
STATES[cajsr] = (CONSTANTS[celltype]==1.00000 ? 1.8102 : CONSTANTS[celltype]==2.00000 ? 1.9593 : 1.5214);
STATES[cai] = (CONSTANTS[celltype]==1.00000 ? 6.63E-05 : CONSTANTS[celltype]==2.00000 ? 8.17E-05 : 8.1583e-05);
CONSTANTS[cli] = 24.0;
CONSTANTS[PKNa] = 0.01833;
CONSTANTS[gkatp] = 4.3195;
CONSTANTS[fkatp] = 0.0;
CONSTANTS[K_o_n] = 5;
CONSTANTS[A_atp] = 2;
CONSTANTS[K_atp] = 0.25;
STATES[m] = (CONSTANTS[celltype]==1.00000 ? 7.43E-04 : CONSTANTS[celltype]==2.00000 ? 7.38E-04 : 8.0572e-4);
STATES[h] = (CONSTANTS[celltype]==1.00000 ? 0.836 : CONSTANTS[celltype]==2.00000 ? 0.8365 : 0.8286);
STATES[j] = (CONSTANTS[celltype]==1.00000 ? 0.8359 : CONSTANTS[celltype]==2.00000 ? 0.8363 : 0.8284);
STATES[hp] = (CONSTANTS[celltype]==1.00000 ? 0.6828 : CONSTANTS[celltype]==2.00000 ? 0.6838 : 0.6707);
STATES[jp] = (CONSTANTS[celltype]==1.00000 ? 0.8357 : CONSTANTS[celltype]==2.00000 ? 0.8358 : 0.8281);
CONSTANTS[GNa] = 11.7802;
STATES[mL] = (CONSTANTS[celltype]==1.00000 ? 1.52E-04 : CONSTANTS[celltype]==2.00000 ? 1.51E-04 : 1.629e-4);
CONSTANTS[thL] = 200;
STATES[hL] = (CONSTANTS[celltype]==1.00000 ? 0.5401 : CONSTANTS[celltype]==2.00000 ? 0.5327 : 0.5255);
STATES[hLp] = (CONSTANTS[celltype]==1.00000 ? 0.3034 : CONSTANTS[celltype]==2.00000 ? 0.2834 : 0.2872);
CONSTANTS[GNaL_b] = 0.0279;
CONSTANTS[Gto_b] = 0.16;
STATES[a] = (CONSTANTS[celltype]==1.00000 ? 9.27E-04 : CONSTANTS[celltype]==2.00000 ? 9.25E-04 : 9.5098e-4);
CONSTANTS[EKshift] = 0;
STATES[iF] = 0.9996;
STATES[iS] = (CONSTANTS[celltype]==1.00000 ? 0.9996 : CONSTANTS[celltype]==2.00000 ? 0.5671 : 0.5936);
STATES[ap] = (CONSTANTS[celltype]==1.00000 ? 4.72E-04 : CONSTANTS[celltype]==2.00000 ? 4.71E-04 : 4.8454e-4);
STATES[iFp] = 0.9996;
STATES[iSp] = (CONSTANTS[celltype]==1.00000 ? 0.9996 : CONSTANTS[celltype]==2.00000 ? 0.6261 :0.6538);
CONSTANTS[Kmn] = 0.002;
CONSTANTS[k2n] = 500;
CONSTANTS[PCa_b] = 8.3757e-05;
STATES[d] = (CONSTANTS[celltype]==1.00000 ? 0.0 : CONSTANTS[celltype]==2.00000 ? 0.0 : 8.1084e-9);
CONSTANTS[Aff] = 0.6;
STATES[ff] = 1.0;
STATES[fs] = (CONSTANTS[celltype]==1.00000 ? 0.9485 : CONSTANTS[celltype]==2.00000 ? 0.92 : 0.939);
STATES[fcaf] = 1.0;
STATES[fcas] = 0.9999;
STATES[jca] = 1.0;
STATES[ffp] = 1.0;
STATES[fcafp] = 1.0;
STATES[nca_ss] = (CONSTANTS[celltype]==1.00000 ? 3.09E-04 : CONSTANTS[celltype]==2.00000 ? 5.14E-04 : 6.6462e-4);
STATES[nca_i] = (CONSTANTS[celltype]==1.00000 ? 5.30E-04 : CONSTANTS[celltype]==2.00000 ? 0.0012 : 0.0012);
CONSTANTS[tjca] = 75;
CONSTANTS[vShift] = 0;
CONSTANTS[offset] = 0;
CONSTANTS[dielConstant] = 74;
CONSTANTS[ICaL_fractionSS] = 0.8;
CONSTANTS[GKr_b] = 0.0321;
STATES[C1] = (CONSTANTS[celltype]==1.00000 ? 6.79E-04 : CONSTANTS[celltype]==2.00000 ? 6.96E-04 : 7.0344e-4);
STATES[C2] = (CONSTANTS[celltype]==1.00000 ? 8.29E-04 : CONSTANTS[celltype]==2.00000 ? 8.27E-04 : 8.5109e-4);
STATES[C3] = (CONSTANTS[celltype]==1.00000 ? 0.9982 : CONSTANTS[celltype]==2.00000 ? 0.9979 : 0.9981);
STATES[I] = (CONSTANTS[celltype]==1.00000 ? 9.54E-06 : CONSTANTS[celltype]==2.00000 ? 1.88E-05 : 1.3289e-5);
STATES[O] = (CONSTANTS[celltype]==1.00000 ? 2.76E-04 : CONSTANTS[celltype]==2.00000 ? 5.42E-04 : 3.7585e-4);
CONSTANTS[alpha_1] = 0.154375;
CONSTANTS[beta_1] = 0.1911;
CONSTANTS[GKs_b] = 0.0011;
STATES[xs1] = (CONSTANTS[celltype]==1.00000 ? 0.2309 : CONSTANTS[celltype]==2.00000 ? 0.2653 : 0.248);
STATES[xs2] = (CONSTANTS[celltype]==1.00000 ? 1.70E-04 : CONSTANTS[celltype]==2.00000 ? 1.69E-04 : 1.7707e-4);
CONSTANTS[GK1_b] = 0.6992;
CONSTANTS[INaCa_fractionSS] = 0.35;
CONSTANTS[kna1] = 15;
CONSTANTS[kna2] = 5;
CONSTANTS[kna3] = 88.12;
CONSTANTS[kasymm] = 12.5;
CONSTANTS[wna] = 6e4;
CONSTANTS[wca] = 6e4;
CONSTANTS[wnaca] = 5e3;
CONSTANTS[kcaon] = 1.5e6;
CONSTANTS[kcaoff] = 5e3;
CONSTANTS[qna] = 0.5224;
CONSTANTS[qca] = 0.167;
CONSTANTS[KmCaAct] = 150e-6;
CONSTANTS[Gncx_b] = 0.0034;
CONSTANTS[k1p] = 949.5;
CONSTANTS[k1m] = 182.4;
CONSTANTS[k2p] = 687.2;
CONSTANTS[k2m] = 39.4;
CONSTANTS[k3p] = 1899;
CONSTANTS[k3m] = 79300;
CONSTANTS[k4p] = 639;
CONSTANTS[k4m] = 40;
CONSTANTS[Knai0] = 9.073;
CONSTANTS[Knao0] = 27.78;
CONSTANTS[delta] = -0.155;
CONSTANTS[Kki] = 0.5;
CONSTANTS[Kko] = 0.3582;
CONSTANTS[MgADP] = 0.05;
CONSTANTS[MgATP] = 9.8;
CONSTANTS[Kmgatp] = 1.698e-7;
CONSTANTS[H] = 1e-7;
CONSTANTS[eP] = 4.2;
CONSTANTS[Khp] = 1.698e-7;
CONSTANTS[Knap] = 224;
CONSTANTS[Kxkur] = 292;
CONSTANTS[Pnak_b] = 15.4509;
CONSTANTS[GKb_b] = 0.0189;
CONSTANTS[PNab] = 1.9239e-09;
CONSTANTS[PCab] = 5.9194e-08;
CONSTANTS[GpCa] = 5e-04;
CONSTANTS[KmCap] = 0.0005;
CONSTANTS[GClCa] = 0.2843;
CONSTANTS[GClb] = 1.98e-3;
CONSTANTS[KdClCa] = 0.1;
CONSTANTS[Fjunc] = 1;
CONSTANTS[tauNa] = 2.0;
CONSTANTS[tauK] = 2.0;
CONSTANTS[tauCa] = 0.2;
CONSTANTS[bt] = 4.75;
STATES[Jrel_np] = (CONSTANTS[celltype]==1.00000 ? 2.82E-24 : CONSTANTS[celltype]==2.00000 ? 0. : 1.6129e-22);
STATES[Jrel_p] = (CONSTANTS[celltype]==1.00000 ? 0. : CONSTANTS[celltype]==2.00000 ? 0. : 1.2475e-20);
CONSTANTS[cajsr_half] = 1.7;
CONSTANTS[Jrel_b] = 1.5378;
CONSTANTS[Jup_b] = 1.0;
CONSTANTS[vcell] =  1000.00*3.14000*CONSTANTS[rad]*CONSTANTS[rad]*CONSTANTS[L];
CONSTANTS[cmdnmax] = (CONSTANTS[celltype]==1.00000 ?  CONSTANTS[cmdnmax_b]*1.30000 : CONSTANTS[cmdnmax_b]);
CONSTANTS[ECl] =  (( CONSTANTS[R]*CONSTANTS[T])/( CONSTANTS[zcl]*CONSTANTS[F]))*log(CONSTANTS[clo]/CONSTANTS[cli]);
CONSTANTS[akik] = pow(CONSTANTS[ko]/CONSTANTS[K_o_n], 0.240000);
CONSTANTS[bkik] = 1.00000/(1.00000+pow(CONSTANTS[A_atp]/CONSTANTS[K_atp], 2.00000));
CONSTANTS[thLp] =  3.00000*CONSTANTS[thL];
CONSTANTS[GNaL] = (CONSTANTS[celltype]==1.00000 ?  CONSTANTS[GNaL_b]*0.600000 : CONSTANTS[GNaL_b]);
CONSTANTS[Gto] = (CONSTANTS[celltype]==1.00000 ?  CONSTANTS[Gto_b]*2.00000 : CONSTANTS[celltype]==2.00000 ?  CONSTANTS[Gto_b]*2.00000 : CONSTANTS[Gto_b]);
CONSTANTS[Afs] = 1.00000 - CONSTANTS[Aff];
CONSTANTS[PCa] = (CONSTANTS[celltype]==1.00000 ?  CONSTANTS[PCa_b]*1.20000 : CONSTANTS[celltype]==2.00000 ?  CONSTANTS[PCa_b]*2.00000 : CONSTANTS[PCa_b]);
CONSTANTS[Io] = ( 0.500000*(CONSTANTS[nao]+CONSTANTS[ko]+CONSTANTS[clo]+ 4.00000*CONSTANTS[cao]))/1000.00;
CONSTANTS[GKr] = (CONSTANTS[celltype]==1.00000 ?  CONSTANTS[GKr_b]*1.30000 : CONSTANTS[celltype]==2.00000 ?  CONSTANTS[GKr_b]*0.800000 : CONSTANTS[GKr_b]);
CONSTANTS[GKs] = (CONSTANTS[celltype]==1.00000 ?  CONSTANTS[GKs_b]*1.40000 : CONSTANTS[GKs_b]);
CONSTANTS[GK1] = (CONSTANTS[celltype]==1.00000 ?  CONSTANTS[GK1_b]*1.20000 : CONSTANTS[celltype]==2.00000 ?  CONSTANTS[GK1_b]*1.30000 : CONSTANTS[GK1_b]);
CONSTANTS[GKb] = (CONSTANTS[celltype]==1.00000 ?  CONSTANTS[GKb_b]*0.600000 : CONSTANTS[GKb_b]);
CONSTANTS[a_rel] = ( 0.500000*CONSTANTS[bt])/1.00000;
CONSTANTS[btp] =  1.25000*CONSTANTS[bt];
CONSTANTS[upScale] = (CONSTANTS[celltype]==1.00000 ? 1.30000 : 1.00000);
CONSTANTS[Ageo] =  2.00000*3.14000*CONSTANTS[rad]*CONSTANTS[rad]+ 2.00000*3.14000*CONSTANTS[rad]*CONSTANTS[L];
CONSTANTS[PCap] =  1.10000*CONSTANTS[PCa];
CONSTANTS[PCaNa] =  0.00125000*CONSTANTS[PCa];
CONSTANTS[PCaK] =  0.000357400*CONSTANTS[PCa];
CONSTANTS[constA] =  1.82000e+06*pow( CONSTANTS[dielConstant]*CONSTANTS[T], - 1.50000);
CONSTANTS[a_relp] = ( 0.500000*CONSTANTS[btp])/1.00000;
CONSTANTS[Acap] =  2.00000*CONSTANTS[Ageo];
CONSTANTS[PCaNap] =  0.00125000*CONSTANTS[PCap];
CONSTANTS[PCaKp] =  0.000357400*CONSTANTS[PCap];
CONSTANTS[gamma_cao] = exp( - CONSTANTS[constA]*4.00000*( pow(CONSTANTS[Io], 1.0 / 2)/(1.00000+ pow(CONSTANTS[Io], 1.0 / 2)) -  0.300000*CONSTANTS[Io]));
CONSTANTS[gamma_nao] = exp( - CONSTANTS[constA]*1.00000*( pow(CONSTANTS[Io], 1.0 / 2)/(1.00000+ pow(CONSTANTS[Io], 1.0 / 2)) -  0.300000*CONSTANTS[Io]));
CONSTANTS[gamma_ko] = exp( - CONSTANTS[constA]*1.00000*( pow(CONSTANTS[Io], 1.0 / 2)/(1.00000+ pow(CONSTANTS[Io], 1.0 / 2)) -  0.300000*CONSTANTS[Io]));
CONSTANTS[vmyo] =  0.680000*CONSTANTS[vcell];
CONSTANTS[vnsr] =  0.0552000*CONSTANTS[vcell];
CONSTANTS[vjsr] =  0.00480000*CONSTANTS[vcell];
CONSTANTS[vss] =  0.0200000*CONSTANTS[vcell];
CONSTANTS[h10_i] = CONSTANTS[kasymm]+1.00000+ (CONSTANTS[nao]/CONSTANTS[kna1])*(1.00000+CONSTANTS[nao]/CONSTANTS[kna2]);
CONSTANTS[h11_i] = ( CONSTANTS[nao]*CONSTANTS[nao])/( CONSTANTS[h10_i]*CONSTANTS[kna1]*CONSTANTS[kna2]);
CONSTANTS[h12_i] = 1.00000/CONSTANTS[h10_i];
CONSTANTS[k1_i] =  CONSTANTS[h12_i]*CONSTANTS[cao]*CONSTANTS[kcaon];
CONSTANTS[k2_i] = CONSTANTS[kcaoff];
CONSTANTS[k5_i] = CONSTANTS[kcaoff];
CONSTANTS[Gncx] = (CONSTANTS[celltype]==1.00000 ?  CONSTANTS[Gncx_b]*1.10000 : CONSTANTS[celltype]==2.00000 ?  CONSTANTS[Gncx_b]*1.40000 : CONSTANTS[Gncx_b]);
CONSTANTS[h10_ss] = CONSTANTS[kasymm]+1.00000+ (CONSTANTS[nao]/CONSTANTS[kna1])*(1.00000+CONSTANTS[nao]/CONSTANTS[kna2]);
CONSTANTS[h11_ss] = ( CONSTANTS[nao]*CONSTANTS[nao])/( CONSTANTS[h10_ss]*CONSTANTS[kna1]*CONSTANTS[kna2]);
CONSTANTS[h12_ss] = 1.00000/CONSTANTS[h10_ss];
CONSTANTS[k1_ss] =  CONSTANTS[h12_ss]*CONSTANTS[cao]*CONSTANTS[kcaon];
CONSTANTS[k2_ss] = CONSTANTS[kcaoff];
CONSTANTS[k5_ss] = CONSTANTS[kcaoff];
CONSTANTS[b1] =  CONSTANTS[k1m]*CONSTANTS[MgADP];
CONSTANTS[a2] = CONSTANTS[k2p];
CONSTANTS[a4] = (( CONSTANTS[k4p]*CONSTANTS[MgATP])/CONSTANTS[Kmgatp])/(1.00000+CONSTANTS[MgATP]/CONSTANTS[Kmgatp]);
CONSTANTS[Pnak] = (CONSTANTS[celltype]==1.00000 ?  CONSTANTS[Pnak_b]*0.900000 : CONSTANTS[celltype]==2.00000 ?  CONSTANTS[Pnak_b]*0.700000 : CONSTANTS[Pnak_b]);
}

void Tomek_model::computeRates( double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC )
{
ALGEBRAIC[hLss] = 1.00000/(1.00000+exp((STATES[v]+87.6100)/7.48800));
ALGEBRAIC[hLssp] = 1.00000/(1.00000+exp((STATES[v]+93.8100)/7.48800));
ALGEBRAIC[jcass] = 1.00000/(1.00000+exp((STATES[v]+18.0800)/2.79160));
ALGEBRAIC[mss] = 1.00000/pow(1.00000+exp(- (STATES[v]+56.8600)/9.03000), 2.00000);
ALGEBRAIC[tm] =  0.129200*exp(- pow((STATES[v]+45.7900)/15.5400, 2.00000))+ 0.0648700*exp(- pow((STATES[v] - 4.82300)/51.1200, 2.00000));
ALGEBRAIC[mLss] = 1.00000/(1.00000+exp(- (STATES[v]+42.8500)/5.26400));
ALGEBRAIC[tmL] =  0.129200*exp(- pow((STATES[v]+45.7900)/15.5400, 2.00000))+ 0.0648700*exp(- pow((STATES[v] - 4.82300)/51.1200, 2.00000));
ALGEBRAIC[ass] = 1.00000/(1.00000+exp(- ((STATES[v]+CONSTANTS[EKshift]) - 14.3400)/14.8200));
ALGEBRAIC[ta] = 1.05150/(1.00000/( 1.20890*(1.00000+exp(- ((STATES[v]+CONSTANTS[EKshift]) - 18.4099)/29.3814)))+3.50000/(1.00000+exp((STATES[v]+CONSTANTS[EKshift]+100.000)/29.3814)));
ALGEBRAIC[dss] = (STATES[v]>=31.4978 ? 1.00000 :  1.07630*exp( - 1.00700*exp( - 0.0829000*STATES[v])));
ALGEBRAIC[td] = CONSTANTS[offset]+0.600000+1.00000/(exp( - 0.0500000*(STATES[v]+CONSTANTS[vShift]+6.00000))+exp( 0.0900000*(STATES[v]+CONSTANTS[vShift]+14.0000)));
ALGEBRAIC[fss] = 1.00000/(1.00000+exp((STATES[v]+19.5800)/3.69600));
ALGEBRAIC[tff] = 7.00000+1.00000/( 0.00450000*exp(- (STATES[v]+20.0000)/10.0000)+ 0.00450000*exp((STATES[v]+20.0000)/10.0000));
ALGEBRAIC[tfs] = 1000.00+1.00000/( 3.50000e-05*exp(- (STATES[v]+5.00000)/4.00000)+ 3.50000e-05*exp((STATES[v]+5.00000)/6.00000));
ALGEBRAIC[km2n] =  STATES[jca]*1.00000;
ALGEBRAIC[anca_ss] = 1.00000/(CONSTANTS[k2n]/ALGEBRAIC[km2n]+pow(1.00000+CONSTANTS[Kmn]/STATES[cass], 4.00000));
ALGEBRAIC[anca_i] = 1.00000/(CONSTANTS[k2n]/ALGEBRAIC[km2n]+pow(1.00000+CONSTANTS[Kmn]/STATES[cai], 4.00000));
ALGEBRAIC[xs1ss] = 1.00000/(1.00000+exp(- (STATES[v]+11.6000)/8.93200));
ALGEBRAIC[txs1] = 817.300+1.00000/( 0.000232600*exp((STATES[v]+48.2800)/17.8000)+ 0.00129200*exp(- (STATES[v]+210.000)/230.000));
ALGEBRAIC[assp] = 1.00000/(1.00000+exp(- ((STATES[v]+CONSTANTS[EKshift]) - 24.3400)/14.8200));
ALGEBRAIC[fcass] = ALGEBRAIC[fss];
ALGEBRAIC[tfcaf] = 7.00000+1.00000/( 0.0400000*exp(- (STATES[v] - 4.00000)/7.00000)+ 0.0400000*exp((STATES[v] - 4.00000)/7.00000));
ALGEBRAIC[tfcas] = 100.000+1.00000/( 0.000120000*exp(- STATES[v]/3.00000)+ 0.000120000*exp(STATES[v]/7.00000));
ALGEBRAIC[tffp] =  2.50000*ALGEBRAIC[tff];
ALGEBRAIC[xs2ss] = ALGEBRAIC[xs1ss];
ALGEBRAIC[txs2] = 1.00000/( 0.0100000*exp((STATES[v] - 50.0000)/20.0000)+ 0.0193000*exp(- (STATES[v]+66.5400)/31.0000));
ALGEBRAIC[CaMKb] = ( CONSTANTS[CaMKo]*(1.00000 - STATES[CaMKt]))/(1.00000+CONSTANTS[KmCaM]/STATES[cass]);
ALGEBRAIC[hss] = 1.00000/pow(1.00000+exp((STATES[v]+71.5500)/7.43000), 2.00000);
ALGEBRAIC[ah] = (STATES[v]>=- 40.0000 ? 0.00000 :  0.0570000*exp(- (STATES[v]+80.0000)/6.80000));
ALGEBRAIC[bh] = (STATES[v]>=- 40.0000 ? 0.770000/( 0.130000*(1.00000+exp(- (STATES[v]+10.6600)/11.1000))) :  2.70000*exp( 0.0790000*STATES[v])+ 310000.*exp( 0.348500*STATES[v]));
ALGEBRAIC[th] = 1.00000/(ALGEBRAIC[ah]+ALGEBRAIC[bh]);
ALGEBRAIC[tfcafp] =  2.50000*ALGEBRAIC[tfcaf];
ALGEBRAIC[jss] = ALGEBRAIC[hss];
ALGEBRAIC[aj] = (STATES[v]>=- 40.0000 ? 0.00000 : ( ( - 25428.0*exp( 0.244400*STATES[v]) -  6.94800e-06*exp( - 0.0439100*STATES[v]))*(STATES[v]+37.7800))/(1.00000+exp( 0.311000*(STATES[v]+79.2300))));
ALGEBRAIC[bj] = (STATES[v]>=- 40.0000 ? ( 0.600000*exp( 0.0570000*STATES[v]))/(1.00000+exp( - 0.100000*(STATES[v]+32.0000))) : ( 0.0242400*exp( - 0.0105200*STATES[v]))/(1.00000+exp( - 0.137800*(STATES[v]+40.1400))));
ALGEBRAIC[tj] = 1.00000/(ALGEBRAIC[aj]+ALGEBRAIC[bj]);
ALGEBRAIC[hssp] = 1.00000/pow(1.00000+exp((STATES[v]+77.5500)/7.43000), 2.00000);
ALGEBRAIC[iss] = 1.00000/(1.00000+exp((STATES[v]+CONSTANTS[EKshift]+43.9400)/5.71100));
ALGEBRAIC[delta_epi] = (CONSTANTS[celltype]==1.00000 ? 1.00000 - 0.950000/(1.00000+exp((STATES[v]+CONSTANTS[EKshift]+70.0000)/5.00000)) : 1.00000);
ALGEBRAIC[tiF_b] = 4.56200+1.00000/( 0.393300*exp(- (STATES[v]+CONSTANTS[EKshift]+100.000)/100.000)+ 0.0800400*exp((STATES[v]+CONSTANTS[EKshift]+50.0000)/16.5900));
ALGEBRAIC[tiF] =  ALGEBRAIC[tiF_b]*ALGEBRAIC[delta_epi];
ALGEBRAIC[vfrt] = ( STATES[v]*CONSTANTS[F])/( CONSTANTS[R]*CONSTANTS[T]);
ALGEBRAIC[alpha] =  0.116100*exp( 0.299000*ALGEBRAIC[vfrt]);
ALGEBRAIC[beta] =  0.244200*exp( - 1.60400*ALGEBRAIC[vfrt]);
ALGEBRAIC[tjp] =  1.46000*ALGEBRAIC[tj];
ALGEBRAIC[tiS_b] = 23.6200+1.00000/( 0.00141600*exp(- (STATES[v]+CONSTANTS[EKshift]+96.5200)/59.0500)+ 1.78000e-08*exp((STATES[v]+CONSTANTS[EKshift]+114.100)/8.07900));
ALGEBRAIC[tiS] =  ALGEBRAIC[tiS_b]*ALGEBRAIC[delta_epi];
ALGEBRAIC[alpha_2] =  0.0578000*exp( 0.971000*ALGEBRAIC[vfrt]);
ALGEBRAIC[beta_2] =  0.000349000*exp( - 1.06200*ALGEBRAIC[vfrt]);
ALGEBRAIC[alpha_i] =  0.253300*exp( 0.595300*ALGEBRAIC[vfrt]);
ALGEBRAIC[beta_i] =  0.0652500*exp( - 0.820900*ALGEBRAIC[vfrt]);
ALGEBRAIC[dti_develop] = 1.35400+0.000100000/(exp(((STATES[v]+CONSTANTS[EKshift]) - 167.400)/15.8900)+exp(- ((STATES[v]+CONSTANTS[EKshift]) - 12.2300)/0.215400));
ALGEBRAIC[dti_recover] = 1.00000 - 0.500000/(1.00000+exp((STATES[v]+CONSTANTS[EKshift]+70.0000)/20.0000));
ALGEBRAIC[tiFp] =  ALGEBRAIC[dti_develop]*ALGEBRAIC[dti_recover]*ALGEBRAIC[tiF];
ALGEBRAIC[tiSp] =  ALGEBRAIC[dti_develop]*ALGEBRAIC[dti_recover]*ALGEBRAIC[tiS];
ALGEBRAIC[alpha_C2ToI] =  5.20000e-05*exp( 1.52500*ALGEBRAIC[vfrt]);
ALGEBRAIC[beta_ItoC2] = ( ALGEBRAIC[beta_2]*ALGEBRAIC[beta_i]*ALGEBRAIC[alpha_C2ToI])/( ALGEBRAIC[alpha_2]*ALGEBRAIC[alpha_i]);
ALGEBRAIC[f] =  CONSTANTS[Aff]*STATES[ff]+ CONSTANTS[Afs]*STATES[fs];
ALGEBRAIC[Afcaf] = 0.300000+0.600000/(1.00000+exp((STATES[v] - 10.0000)/10.0000));
ALGEBRAIC[Afcas] = 1.00000 - ALGEBRAIC[Afcaf];
ALGEBRAIC[fca] =  ALGEBRAIC[Afcaf]*STATES[fcaf]+ ALGEBRAIC[Afcas]*STATES[fcas];
ALGEBRAIC[fp] =  CONSTANTS[Aff]*STATES[ffp]+ CONSTANTS[Afs]*STATES[fs];
ALGEBRAIC[fcap] =  ALGEBRAIC[Afcaf]*STATES[fcafp]+ ALGEBRAIC[Afcas]*STATES[fcas];
ALGEBRAIC[vffrt] = ( STATES[v]*CONSTANTS[F]*CONSTANTS[F])/( CONSTANTS[R]*CONSTANTS[T]);
ALGEBRAIC[Iss] = ( 0.500000*(STATES[nass]+STATES[kss]+CONSTANTS[cli]+ 4.00000*STATES[cass]))/1000.00;
ALGEBRAIC[gamma_cass] = exp( - CONSTANTS[constA]*4.00000*( pow(ALGEBRAIC[Iss], 1.0 / 2)/(1.00000+ pow(ALGEBRAIC[Iss], 1.0 / 2)) -  0.300000*ALGEBRAIC[Iss]));
ALGEBRAIC[PhiCaL_ss] = ( 4.00000*ALGEBRAIC[vffrt]*( ALGEBRAIC[gamma_cass]*STATES[cass]*exp( 2.00000*ALGEBRAIC[vfrt]) -  CONSTANTS[gamma_cao]*CONSTANTS[cao]))/(exp( 2.00000*ALGEBRAIC[vfrt]) - 1.00000);
ALGEBRAIC[CaMKa] = ALGEBRAIC[CaMKb]+STATES[CaMKt];
ALGEBRAIC[fICaLp] = 1.00000/(1.00000+CONSTANTS[KmCaMK]/ALGEBRAIC[CaMKa]);
ALGEBRAIC[ICaL_ss] =  CONSTANTS[ICaL_fractionSS]*( (1.00000 - ALGEBRAIC[fICaLp])*CONSTANTS[PCa]*ALGEBRAIC[PhiCaL_ss]*STATES[d]*( ALGEBRAIC[f]*(1.00000 - STATES[nca_ss])+ STATES[jca]*ALGEBRAIC[fca]*STATES[nca_ss])+ ALGEBRAIC[fICaLp]*CONSTANTS[PCap]*ALGEBRAIC[PhiCaL_ss]*STATES[d]*( ALGEBRAIC[fp]*(1.00000 - STATES[nca_ss])+ STATES[jca]*ALGEBRAIC[fcap]*STATES[nca_ss]));
ALGEBRAIC[Jrel_inf_b] = (( - CONSTANTS[a_rel]*ALGEBRAIC[ICaL_ss])/1.00000)/(1.00000+pow(CONSTANTS[cajsr_half]/STATES[cajsr], 8.00000));
ALGEBRAIC[Jrel_inf] = (CONSTANTS[celltype]==2.00000 ?  ALGEBRAIC[Jrel_inf_b]*1.70000 : ALGEBRAIC[Jrel_inf_b]);
ALGEBRAIC[tau_rel_b] = CONSTANTS[bt]/(1.00000+0.0123000/STATES[cajsr]);
ALGEBRAIC[tau_rel] = (ALGEBRAIC[tau_rel_b]<0.00100000 ? 0.00100000 : ALGEBRAIC[tau_rel_b]);
ALGEBRAIC[Jrel_infp_b] = (( - CONSTANTS[a_relp]*ALGEBRAIC[ICaL_ss])/1.00000)/(1.00000+pow(CONSTANTS[cajsr_half]/STATES[cajsr], 8.00000));
ALGEBRAIC[Jrel_infp] = (CONSTANTS[celltype]==2.00000 ?  ALGEBRAIC[Jrel_infp_b]*1.70000 : ALGEBRAIC[Jrel_infp_b]);
ALGEBRAIC[tau_relp_b] = CONSTANTS[btp]/(1.00000+0.0123000/STATES[cajsr]);
ALGEBRAIC[tau_relp] = (ALGEBRAIC[tau_relp_b]<0.00100000 ? 0.00100000 : ALGEBRAIC[tau_relp_b]);
ALGEBRAIC[EK] =  (( CONSTANTS[R]*CONSTANTS[T])/( CONSTANTS[zk]*CONSTANTS[F]))*log(CONSTANTS[ko]/STATES[ki]);
ALGEBRAIC[AiF] = 1.00000/(1.00000+exp(((STATES[v]+CONSTANTS[EKshift]) - 213.600)/151.200));
ALGEBRAIC[AiS] = 1.00000 - ALGEBRAIC[AiF];
ALGEBRAIC[i] =  ALGEBRAIC[AiF]*STATES[iF]+ ALGEBRAIC[AiS]*STATES[iS];
ALGEBRAIC[ip] =  ALGEBRAIC[AiF]*STATES[iFp]+ ALGEBRAIC[AiS]*STATES[iSp];
ALGEBRAIC[fItop] = 1.00000/(1.00000+CONSTANTS[KmCaMK]/ALGEBRAIC[CaMKa]);
ALGEBRAIC[Ito] =  CONSTANTS[Gto]*(STATES[v] - ALGEBRAIC[EK])*( (1.00000 - ALGEBRAIC[fItop])*STATES[a]*ALGEBRAIC[i]+ ALGEBRAIC[fItop]*STATES[ap]*ALGEBRAIC[ip]);
ALGEBRAIC[IKr] =  CONSTANTS[GKr]* pow((CONSTANTS[ko]/5.00000), 1.0 / 2)*STATES[O]*(STATES[v] - ALGEBRAIC[EK]);
ALGEBRAIC[EKs] =  (( CONSTANTS[R]*CONSTANTS[T])/( CONSTANTS[zk]*CONSTANTS[F]))*log((CONSTANTS[ko]+ CONSTANTS[PKNa]*CONSTANTS[nao])/(STATES[ki]+ CONSTANTS[PKNa]*STATES[nai]));
ALGEBRAIC[KsCa] = 1.00000+0.600000/(1.00000+pow(3.80000e-05/STATES[cai], 1.40000));
ALGEBRAIC[IKs] =  CONSTANTS[GKs]*ALGEBRAIC[KsCa]*STATES[xs1]*STATES[xs2]*(STATES[v] - ALGEBRAIC[EKs]);
ALGEBRAIC[aK1] = 4.09400/(1.00000+exp( 0.121700*((STATES[v] - ALGEBRAIC[EK]) - 49.9340)));
ALGEBRAIC[bK1] = ( 15.7200*exp( 0.0674000*((STATES[v] - ALGEBRAIC[EK]) - 3.25700))+exp( 0.0618000*((STATES[v] - ALGEBRAIC[EK]) - 594.310)))/(1.00000+exp( - 0.162900*((STATES[v] - ALGEBRAIC[EK])+14.2070)));
ALGEBRAIC[K1ss] = ALGEBRAIC[aK1]/(ALGEBRAIC[aK1]+ALGEBRAIC[bK1]);
ALGEBRAIC[IK1] =  CONSTANTS[GK1]* pow((CONSTANTS[ko]/5.00000), 1.0 / 2)*ALGEBRAIC[K1ss]*(STATES[v] - ALGEBRAIC[EK]);
ALGEBRAIC[Knao] =  CONSTANTS[Knao0]*exp(( (1.00000 - CONSTANTS[delta])*ALGEBRAIC[vfrt])/3.00000);
ALGEBRAIC[a3] = ( CONSTANTS[k3p]*pow(CONSTANTS[ko]/CONSTANTS[Kko], 2.00000))/((pow(1.00000+CONSTANTS[nao]/ALGEBRAIC[Knao], 3.00000)+pow(1.00000+CONSTANTS[ko]/CONSTANTS[Kko], 2.00000)) - 1.00000);
ALGEBRAIC[P] = CONSTANTS[eP]/(1.00000+CONSTANTS[H]/CONSTANTS[Khp]+STATES[nai]/CONSTANTS[Knap]+STATES[ki]/CONSTANTS[Kxkur]);
ALGEBRAIC[b3] = ( CONSTANTS[k3m]*ALGEBRAIC[P]*CONSTANTS[H])/(1.00000+CONSTANTS[MgATP]/CONSTANTS[Kmgatp]);
ALGEBRAIC[Knai] =  CONSTANTS[Knai0]*exp(( CONSTANTS[delta]*ALGEBRAIC[vfrt])/3.00000);
ALGEBRAIC[a1] = ( CONSTANTS[k1p]*pow(STATES[nai]/ALGEBRAIC[Knai], 3.00000))/((pow(1.00000+STATES[nai]/ALGEBRAIC[Knai], 3.00000)+pow(1.00000+STATES[ki]/CONSTANTS[Kki], 2.00000)) - 1.00000);
ALGEBRAIC[b2] = ( CONSTANTS[k2m]*pow(CONSTANTS[nao]/ALGEBRAIC[Knao], 3.00000))/((pow(1.00000+CONSTANTS[nao]/ALGEBRAIC[Knao], 3.00000)+pow(1.00000+CONSTANTS[ko]/CONSTANTS[Kko], 2.00000)) - 1.00000);
ALGEBRAIC[b4] = ( CONSTANTS[k4m]*pow(STATES[ki]/CONSTANTS[Kki], 2.00000))/((pow(1.00000+STATES[nai]/ALGEBRAIC[Knai], 3.00000)+pow(1.00000+STATES[ki]/CONSTANTS[Kki], 2.00000)) - 1.00000);
ALGEBRAIC[x1] =  CONSTANTS[a4]*ALGEBRAIC[a1]*CONSTANTS[a2]+ ALGEBRAIC[b2]*ALGEBRAIC[b4]*ALGEBRAIC[b3]+ CONSTANTS[a2]*ALGEBRAIC[b4]*ALGEBRAIC[b3]+ ALGEBRAIC[b3]*ALGEBRAIC[a1]*CONSTANTS[a2];
ALGEBRAIC[x2] =  ALGEBRAIC[b2]*CONSTANTS[b1]*ALGEBRAIC[b4]+ ALGEBRAIC[a1]*CONSTANTS[a2]*ALGEBRAIC[a3]+ ALGEBRAIC[a3]*CONSTANTS[b1]*ALGEBRAIC[b4]+ CONSTANTS[a2]*ALGEBRAIC[a3]*ALGEBRAIC[b4];
ALGEBRAIC[x3] =  CONSTANTS[a2]*ALGEBRAIC[a3]*CONSTANTS[a4]+ ALGEBRAIC[b3]*ALGEBRAIC[b2]*CONSTANTS[b1]+ ALGEBRAIC[b2]*CONSTANTS[b1]*CONSTANTS[a4]+ ALGEBRAIC[a3]*CONSTANTS[a4]*CONSTANTS[b1];
ALGEBRAIC[x4] =  ALGEBRAIC[b4]*ALGEBRAIC[b3]*ALGEBRAIC[b2]+ ALGEBRAIC[a3]*CONSTANTS[a4]*ALGEBRAIC[a1]+ ALGEBRAIC[b2]*CONSTANTS[a4]*ALGEBRAIC[a1]+ ALGEBRAIC[b3]*ALGEBRAIC[b2]*ALGEBRAIC[a1];
ALGEBRAIC[E1] = ALGEBRAIC[x1]/(ALGEBRAIC[x1]+ALGEBRAIC[x2]+ALGEBRAIC[x3]+ALGEBRAIC[x4]);
ALGEBRAIC[E2] = ALGEBRAIC[x2]/(ALGEBRAIC[x1]+ALGEBRAIC[x2]+ALGEBRAIC[x3]+ALGEBRAIC[x4]);
ALGEBRAIC[JnakNa] =  3.00000*( ALGEBRAIC[E1]*ALGEBRAIC[a3] -  ALGEBRAIC[E2]*ALGEBRAIC[b3]);
ALGEBRAIC[E3] = ALGEBRAIC[x3]/(ALGEBRAIC[x1]+ALGEBRAIC[x2]+ALGEBRAIC[x3]+ALGEBRAIC[x4]);
ALGEBRAIC[E4] = ALGEBRAIC[x4]/(ALGEBRAIC[x1]+ALGEBRAIC[x2]+ALGEBRAIC[x3]+ALGEBRAIC[x4]);
ALGEBRAIC[JnakK] =  2.00000*( ALGEBRAIC[E4]*CONSTANTS[b1] -  ALGEBRAIC[E3]*ALGEBRAIC[a1]);
ALGEBRAIC[INaK] =  CONSTANTS[Pnak]*( CONSTANTS[zna]*ALGEBRAIC[JnakNa]+ CONSTANTS[zk]*ALGEBRAIC[JnakK]);
ALGEBRAIC[xkb] = 1.00000/(1.00000+exp(- (STATES[v] - 10.8968)/23.9871));
ALGEBRAIC[IKb] =  CONSTANTS[GKb]*ALGEBRAIC[xkb]*(STATES[v] - ALGEBRAIC[EK]);
ALGEBRAIC[I_katp] =  CONSTANTS[fkatp]*CONSTANTS[gkatp]*CONSTANTS[akik]*CONSTANTS[bkik]*(STATES[v] - ALGEBRAIC[EK]);
ALGEBRAIC[Istim] = (TIME>=CONSTANTS[stim_start]&&TIME<=CONSTANTS[i_Stim_End]&&(TIME - CONSTANTS[stim_start]) -  floor((TIME - CONSTANTS[stim_start])/CONSTANTS[BCL])*CONSTANTS[BCL]<=CONSTANTS[i_Stim_PulseDuration] ? CONSTANTS[i_Stim_Amplitude] : 0.00000);
ALGEBRAIC[Ii] = ( 0.500000*(STATES[nai]+STATES[ki]+CONSTANTS[cli]+ 4.00000*STATES[cai]))/1000.00;
ALGEBRAIC[gamma_ki] = exp( - CONSTANTS[constA]*1.00000*( pow(ALGEBRAIC[Ii], 1.0 / 2)/(1.00000+ pow(ALGEBRAIC[Ii], 1.0 / 2)) -  0.300000*ALGEBRAIC[Ii]));
ALGEBRAIC[PhiCaK_i] = ( 1.00000*ALGEBRAIC[vffrt]*( ALGEBRAIC[gamma_ki]*STATES[ki]*exp( 1.00000*ALGEBRAIC[vfrt]) -  CONSTANTS[gamma_ko]*CONSTANTS[ko]))/(exp( 1.00000*ALGEBRAIC[vfrt]) - 1.00000);
ALGEBRAIC[ICaK_i] =  (1.00000 - CONSTANTS[ICaL_fractionSS])*( (1.00000 - ALGEBRAIC[fICaLp])*CONSTANTS[PCaK]*ALGEBRAIC[PhiCaK_i]*STATES[d]*( ALGEBRAIC[f]*(1.00000 - STATES[nca_i])+ STATES[jca]*ALGEBRAIC[fca]*STATES[nca_i])+ ALGEBRAIC[fICaLp]*CONSTANTS[PCaKp]*ALGEBRAIC[PhiCaK_i]*STATES[d]*( ALGEBRAIC[fp]*(1.00000 - STATES[nca_i])+ STATES[jca]*ALGEBRAIC[fcap]*STATES[nca_i]));
ALGEBRAIC[JdiffK] = (STATES[kss] - STATES[ki])/CONSTANTS[tauK];
ALGEBRAIC[gamma_kss] = exp( - CONSTANTS[constA]*1.00000*( pow(ALGEBRAIC[Iss], 1.0 / 2)/(1.00000+ pow(ALGEBRAIC[Iss], 1.0 / 2)) -  0.300000*ALGEBRAIC[Iss]));
ALGEBRAIC[PhiCaK_ss] = ( 1.00000*ALGEBRAIC[vffrt]*( ALGEBRAIC[gamma_kss]*STATES[kss]*exp( 1.00000*ALGEBRAIC[vfrt]) -  CONSTANTS[gamma_ko]*CONSTANTS[ko]))/(exp( 1.00000*ALGEBRAIC[vfrt]) - 1.00000);
ALGEBRAIC[ICaK_ss] =  CONSTANTS[ICaL_fractionSS]*( (1.00000 - ALGEBRAIC[fICaLp])*CONSTANTS[PCaK]*ALGEBRAIC[PhiCaK_ss]*STATES[d]*( ALGEBRAIC[f]*(1.00000 - STATES[nca_ss])+ STATES[jca]*ALGEBRAIC[fca]*STATES[nca_ss])+ ALGEBRAIC[fICaLp]*CONSTANTS[PCaKp]*ALGEBRAIC[PhiCaK_ss]*STATES[d]*( ALGEBRAIC[fp]*(1.00000 - STATES[nca_ss])+ STATES[jca]*ALGEBRAIC[fcap]*STATES[nca_ss]));
ALGEBRAIC[ENa] =  (( CONSTANTS[R]*CONSTANTS[T])/( CONSTANTS[zna]*CONSTANTS[F]))*log(CONSTANTS[nao]/STATES[nai]);
ALGEBRAIC[fINap] = 1.00000/(1.00000+CONSTANTS[KmCaMK]/ALGEBRAIC[CaMKa]);
ALGEBRAIC[INa] =  CONSTANTS[GNa]*(STATES[v] - ALGEBRAIC[ENa])*pow(STATES[m], 3.00000)*( (1.00000 - ALGEBRAIC[fINap])*STATES[h]*STATES[j]+ ALGEBRAIC[fINap]*STATES[hp]*STATES[jp]);
ALGEBRAIC[fINaLp] = 1.00000/(1.00000+CONSTANTS[KmCaMK]/ALGEBRAIC[CaMKa]);
ALGEBRAIC[INaL] =  CONSTANTS[GNaL]*(STATES[v] - ALGEBRAIC[ENa])*STATES[mL]*( (1.00000 - ALGEBRAIC[fINaLp])*STATES[hL]+ ALGEBRAIC[fINaLp]*STATES[hLp]);
ALGEBRAIC[allo_i] = 1.00000/(1.00000+pow(CONSTANTS[KmCaAct]/STATES[cai], 2.00000));
ALGEBRAIC[hna] = exp( CONSTANTS[qna]*ALGEBRAIC[vfrt]);
ALGEBRAIC[h7_i] = 1.00000+ (CONSTANTS[nao]/CONSTANTS[kna3])*(1.00000+1.00000/ALGEBRAIC[hna]);
ALGEBRAIC[h8_i] = CONSTANTS[nao]/( CONSTANTS[kna3]*ALGEBRAIC[hna]*ALGEBRAIC[h7_i]);
ALGEBRAIC[k3pp_i] =  ALGEBRAIC[h8_i]*CONSTANTS[wnaca];
ALGEBRAIC[h1_i] = 1.00000+ (STATES[nai]/CONSTANTS[kna3])*(1.00000+ALGEBRAIC[hna]);
ALGEBRAIC[h2_i] = ( STATES[nai]*ALGEBRAIC[hna])/( CONSTANTS[kna3]*ALGEBRAIC[h1_i]);
ALGEBRAIC[k4pp_i] =  ALGEBRAIC[h2_i]*CONSTANTS[wnaca];
ALGEBRAIC[h4_i] = 1.00000+ (STATES[nai]/CONSTANTS[kna1])*(1.00000+STATES[nai]/CONSTANTS[kna2]);
ALGEBRAIC[h5_i] = ( STATES[nai]*STATES[nai])/( ALGEBRAIC[h4_i]*CONSTANTS[kna1]*CONSTANTS[kna2]);
ALGEBRAIC[k7_i] =  ALGEBRAIC[h5_i]*ALGEBRAIC[h2_i]*CONSTANTS[wna];
ALGEBRAIC[k8_i] =  ALGEBRAIC[h8_i]*CONSTANTS[h11_i]*CONSTANTS[wna];
ALGEBRAIC[h9_i] = 1.00000/ALGEBRAIC[h7_i];
ALGEBRAIC[k3p_i] =  ALGEBRAIC[h9_i]*CONSTANTS[wca];
ALGEBRAIC[k3_i] = ALGEBRAIC[k3p_i]+ALGEBRAIC[k3pp_i];
ALGEBRAIC[hca] = exp( CONSTANTS[qca]*ALGEBRAIC[vfrt]);
ALGEBRAIC[h3_i] = 1.00000/ALGEBRAIC[h1_i];
ALGEBRAIC[k4p_i] = ( ALGEBRAIC[h3_i]*CONSTANTS[wca])/ALGEBRAIC[hca];
ALGEBRAIC[k4_i] = ALGEBRAIC[k4p_i]+ALGEBRAIC[k4pp_i];
ALGEBRAIC[h6_i] = 1.00000/ALGEBRAIC[h4_i];
ALGEBRAIC[k6_i] =  ALGEBRAIC[h6_i]*STATES[cai]*CONSTANTS[kcaon];
ALGEBRAIC[x1_i] =  CONSTANTS[k2_i]*ALGEBRAIC[k4_i]*(ALGEBRAIC[k7_i]+ALGEBRAIC[k6_i])+ CONSTANTS[k5_i]*ALGEBRAIC[k7_i]*(CONSTANTS[k2_i]+ALGEBRAIC[k3_i]);
ALGEBRAIC[x2_i] =  CONSTANTS[k1_i]*ALGEBRAIC[k7_i]*(ALGEBRAIC[k4_i]+CONSTANTS[k5_i])+ ALGEBRAIC[k4_i]*ALGEBRAIC[k6_i]*(CONSTANTS[k1_i]+ALGEBRAIC[k8_i]);
ALGEBRAIC[x3_i] =  CONSTANTS[k1_i]*ALGEBRAIC[k3_i]*(ALGEBRAIC[k7_i]+ALGEBRAIC[k6_i])+ ALGEBRAIC[k8_i]*ALGEBRAIC[k6_i]*(CONSTANTS[k2_i]+ALGEBRAIC[k3_i]);
ALGEBRAIC[x4_i] =  CONSTANTS[k2_i]*ALGEBRAIC[k8_i]*(ALGEBRAIC[k4_i]+CONSTANTS[k5_i])+ ALGEBRAIC[k3_i]*CONSTANTS[k5_i]*(CONSTANTS[k1_i]+ALGEBRAIC[k8_i]);
ALGEBRAIC[E1_i] = ALGEBRAIC[x1_i]/(ALGEBRAIC[x1_i]+ALGEBRAIC[x2_i]+ALGEBRAIC[x3_i]+ALGEBRAIC[x4_i]);
ALGEBRAIC[E2_i] = ALGEBRAIC[x2_i]/(ALGEBRAIC[x1_i]+ALGEBRAIC[x2_i]+ALGEBRAIC[x3_i]+ALGEBRAIC[x4_i]);
ALGEBRAIC[E3_i] = ALGEBRAIC[x3_i]/(ALGEBRAIC[x1_i]+ALGEBRAIC[x2_i]+ALGEBRAIC[x3_i]+ALGEBRAIC[x4_i]);
ALGEBRAIC[E4_i] = ALGEBRAIC[x4_i]/(ALGEBRAIC[x1_i]+ALGEBRAIC[x2_i]+ALGEBRAIC[x3_i]+ALGEBRAIC[x4_i]);
ALGEBRAIC[JncxNa_i] = ( 3.00000*( ALGEBRAIC[E4_i]*ALGEBRAIC[k7_i] -  ALGEBRAIC[E1_i]*ALGEBRAIC[k8_i])+ ALGEBRAIC[E3_i]*ALGEBRAIC[k4pp_i]) -  ALGEBRAIC[E2_i]*ALGEBRAIC[k3pp_i];
ALGEBRAIC[JncxCa_i] =  ALGEBRAIC[E2_i]*CONSTANTS[k2_i] -  ALGEBRAIC[E1_i]*CONSTANTS[k1_i];
ALGEBRAIC[INaCa_i] =  (1.00000 - CONSTANTS[INaCa_fractionSS])*CONSTANTS[Gncx]*ALGEBRAIC[allo_i]*( CONSTANTS[zna]*ALGEBRAIC[JncxNa_i]+ CONSTANTS[zca]*ALGEBRAIC[JncxCa_i]);
ALGEBRAIC[INab] = ( CONSTANTS[PNab]*ALGEBRAIC[vffrt]*( STATES[nai]*exp(ALGEBRAIC[vfrt]) - CONSTANTS[nao]))/(exp(ALGEBRAIC[vfrt]) - 1.00000);
ALGEBRAIC[gamma_nai] = exp( - CONSTANTS[constA]*1.00000*( pow(ALGEBRAIC[Ii], 1.0 / 2)/(1.00000+ pow(ALGEBRAIC[Ii], 1.0 / 2)) -  0.300000*ALGEBRAIC[Ii]));
ALGEBRAIC[PhiCaNa_i] = ( 1.00000*ALGEBRAIC[vffrt]*( ALGEBRAIC[gamma_nai]*STATES[nai]*exp( 1.00000*ALGEBRAIC[vfrt]) -  CONSTANTS[gamma_nao]*CONSTANTS[nao]))/(exp( 1.00000*ALGEBRAIC[vfrt]) - 1.00000);
ALGEBRAIC[ICaNa_i] =  (1.00000 - CONSTANTS[ICaL_fractionSS])*( (1.00000 - ALGEBRAIC[fICaLp])*CONSTANTS[PCaNa]*ALGEBRAIC[PhiCaNa_i]*STATES[d]*( ALGEBRAIC[f]*(1.00000 - STATES[nca_i])+ STATES[jca]*ALGEBRAIC[fca]*STATES[nca_i])+ ALGEBRAIC[fICaLp]*CONSTANTS[PCaNap]*ALGEBRAIC[PhiCaNa_i]*STATES[d]*( ALGEBRAIC[fp]*(1.00000 - STATES[nca_i])+ STATES[jca]*ALGEBRAIC[fcap]*STATES[nca_i]));
ALGEBRAIC[JdiffNa] = (STATES[nass] - STATES[nai])/CONSTANTS[tauNa];
ALGEBRAIC[allo_ss] = 1.00000/(1.00000+pow(CONSTANTS[KmCaAct]/STATES[cass], 2.00000));
ALGEBRAIC[h7_ss] = 1.00000+ (CONSTANTS[nao]/CONSTANTS[kna3])*(1.00000+1.00000/ALGEBRAIC[hna]);
ALGEBRAIC[h8_ss] = CONSTANTS[nao]/( CONSTANTS[kna3]*ALGEBRAIC[hna]*ALGEBRAIC[h7_ss]);
ALGEBRAIC[k3pp_ss] =  ALGEBRAIC[h8_ss]*CONSTANTS[wnaca];
ALGEBRAIC[h1_ss] = 1.00000+ (STATES[nass]/CONSTANTS[kna3])*(1.00000+ALGEBRAIC[hna]);
ALGEBRAIC[h2_ss] = ( STATES[nass]*ALGEBRAIC[hna])/( CONSTANTS[kna3]*ALGEBRAIC[h1_ss]);
ALGEBRAIC[k4pp_ss] =  ALGEBRAIC[h2_ss]*CONSTANTS[wnaca];
ALGEBRAIC[h4_ss] = 1.00000+ (STATES[nass]/CONSTANTS[kna1])*(1.00000+STATES[nass]/CONSTANTS[kna2]);
ALGEBRAIC[h5_ss] = ( STATES[nass]*STATES[nass])/( ALGEBRAIC[h4_ss]*CONSTANTS[kna1]*CONSTANTS[kna2]);
ALGEBRAIC[k7_ss] =  ALGEBRAIC[h5_ss]*ALGEBRAIC[h2_ss]*CONSTANTS[wna];
ALGEBRAIC[k8_ss] =  ALGEBRAIC[h8_ss]*CONSTANTS[h11_ss]*CONSTANTS[wna];
ALGEBRAIC[h9_ss] = 1.00000/ALGEBRAIC[h7_ss];
ALGEBRAIC[k3p_ss] =  ALGEBRAIC[h9_ss]*CONSTANTS[wca];
ALGEBRAIC[k3_ss] = ALGEBRAIC[k3p_ss]+ALGEBRAIC[k3pp_ss];
ALGEBRAIC[h3_ss] = 1.00000/ALGEBRAIC[h1_ss];
ALGEBRAIC[k4p_ss] = ( ALGEBRAIC[h3_ss]*CONSTANTS[wca])/ALGEBRAIC[hca];
ALGEBRAIC[k4_ss] = ALGEBRAIC[k4p_ss]+ALGEBRAIC[k4pp_ss];
ALGEBRAIC[h6_ss] = 1.00000/ALGEBRAIC[h4_ss];
ALGEBRAIC[k6_ss] =  ALGEBRAIC[h6_ss]*STATES[cass]*CONSTANTS[kcaon];
ALGEBRAIC[x1_ss] =  CONSTANTS[k2_ss]*ALGEBRAIC[k4_ss]*(ALGEBRAIC[k7_ss]+ALGEBRAIC[k6_ss])+ CONSTANTS[k5_ss]*ALGEBRAIC[k7_ss]*(CONSTANTS[k2_ss]+ALGEBRAIC[k3_ss]);
ALGEBRAIC[x2_ss] =  CONSTANTS[k1_ss]*ALGEBRAIC[k7_ss]*(ALGEBRAIC[k4_ss]+CONSTANTS[k5_ss])+ ALGEBRAIC[k4_ss]*ALGEBRAIC[k6_ss]*(CONSTANTS[k1_ss]+ALGEBRAIC[k8_ss]);
ALGEBRAIC[x3_ss] =  CONSTANTS[k1_ss]*ALGEBRAIC[k3_ss]*(ALGEBRAIC[k7_ss]+ALGEBRAIC[k6_ss])+ ALGEBRAIC[k8_ss]*ALGEBRAIC[k6_ss]*(CONSTANTS[k2_ss]+ALGEBRAIC[k3_ss]);
ALGEBRAIC[x4_ss] =  CONSTANTS[k2_ss]*ALGEBRAIC[k8_ss]*(ALGEBRAIC[k4_ss]+CONSTANTS[k5_ss])+ ALGEBRAIC[k3_ss]*CONSTANTS[k5_ss]*(CONSTANTS[k1_ss]+ALGEBRAIC[k8_ss]);
ALGEBRAIC[E1_ss] = ALGEBRAIC[x1_ss]/(ALGEBRAIC[x1_ss]+ALGEBRAIC[x2_ss]+ALGEBRAIC[x3_ss]+ALGEBRAIC[x4_ss]);
ALGEBRAIC[E2_ss] = ALGEBRAIC[x2_ss]/(ALGEBRAIC[x1_ss]+ALGEBRAIC[x2_ss]+ALGEBRAIC[x3_ss]+ALGEBRAIC[x4_ss]);
ALGEBRAIC[E3_ss] = ALGEBRAIC[x3_ss]/(ALGEBRAIC[x1_ss]+ALGEBRAIC[x2_ss]+ALGEBRAIC[x3_ss]+ALGEBRAIC[x4_ss]);
ALGEBRAIC[E4_ss] = ALGEBRAIC[x4_ss]/(ALGEBRAIC[x1_ss]+ALGEBRAIC[x2_ss]+ALGEBRAIC[x3_ss]+ALGEBRAIC[x4_ss]);
ALGEBRAIC[JncxNa_ss] = ( 3.00000*( ALGEBRAIC[E4_ss]*ALGEBRAIC[k7_ss] -  ALGEBRAIC[E1_ss]*ALGEBRAIC[k8_ss])+ ALGEBRAIC[E3_ss]*ALGEBRAIC[k4pp_ss]) -  ALGEBRAIC[E2_ss]*ALGEBRAIC[k3pp_ss];
ALGEBRAIC[JncxCa_ss] =  ALGEBRAIC[E2_ss]*CONSTANTS[k2_ss] -  ALGEBRAIC[E1_ss]*CONSTANTS[k1_ss];
ALGEBRAIC[INaCa_ss] =  CONSTANTS[INaCa_fractionSS]*CONSTANTS[Gncx]*ALGEBRAIC[allo_ss]*( CONSTANTS[zna]*ALGEBRAIC[JncxNa_ss]+ CONSTANTS[zca]*ALGEBRAIC[JncxCa_ss]);
ALGEBRAIC[gamma_nass] = exp( - CONSTANTS[constA]*1.00000*( pow(ALGEBRAIC[Iss], 1.0 / 2)/(1.00000+ pow(ALGEBRAIC[Iss], 1.0 / 2)) -  0.300000*ALGEBRAIC[Iss]));
ALGEBRAIC[PhiCaNa_ss] = ( 1.00000*ALGEBRAIC[vffrt]*( ALGEBRAIC[gamma_nass]*STATES[nass]*exp( 1.00000*ALGEBRAIC[vfrt]) -  CONSTANTS[gamma_nao]*CONSTANTS[nao]))/(exp( 1.00000*ALGEBRAIC[vfrt]) - 1.00000);
ALGEBRAIC[ICaNa_ss] =  CONSTANTS[ICaL_fractionSS]*( (1.00000 - ALGEBRAIC[fICaLp])*CONSTANTS[PCaNa]*ALGEBRAIC[PhiCaNa_ss]*STATES[d]*( ALGEBRAIC[f]*(1.00000 - STATES[nca_ss])+ STATES[jca]*ALGEBRAIC[fca]*STATES[nca_ss])+ ALGEBRAIC[fICaLp]*CONSTANTS[PCaNap]*ALGEBRAIC[PhiCaNa_ss]*STATES[d]*( ALGEBRAIC[fp]*(1.00000 - STATES[nca_ss])+ STATES[jca]*ALGEBRAIC[fcap]*STATES[nca_ss]));
ALGEBRAIC[Jdiff] = (STATES[cass] - STATES[cai])/CONSTANTS[tauCa];
ALGEBRAIC[fJrelp] = 1.00000/(1.00000+CONSTANTS[KmCaMK]/ALGEBRAIC[CaMKa]);
ALGEBRAIC[Jrel] =  CONSTANTS[Jrel_b]*( (1.00000 - ALGEBRAIC[fJrelp])*STATES[Jrel_np]+ ALGEBRAIC[fJrelp]*STATES[Jrel_p]);
ALGEBRAIC[Bcass] = 1.00000/(1.00000+( CONSTANTS[BSRmax]*CONSTANTS[KmBSR])/pow(CONSTANTS[KmBSR]+STATES[cass], 2.00000)+( CONSTANTS[BSLmax]*CONSTANTS[KmBSL])/pow(CONSTANTS[KmBSL]+STATES[cass], 2.00000));
ALGEBRAIC[gamma_cai] = exp( - CONSTANTS[constA]*4.00000*( pow(ALGEBRAIC[Ii], 1.0 / 2)/(1.00000+ pow(ALGEBRAIC[Ii], 1.0 / 2)) -  0.300000*ALGEBRAIC[Ii]));
ALGEBRAIC[PhiCaL_i] = ( 4.00000*ALGEBRAIC[vffrt]*( ALGEBRAIC[gamma_cai]*STATES[cai]*exp( 2.00000*ALGEBRAIC[vfrt]) -  CONSTANTS[gamma_cao]*CONSTANTS[cao]))/(exp( 2.00000*ALGEBRAIC[vfrt]) - 1.00000);
ALGEBRAIC[ICaL_i] =  (1.00000 - CONSTANTS[ICaL_fractionSS])*( (1.00000 - ALGEBRAIC[fICaLp])*CONSTANTS[PCa]*ALGEBRAIC[PhiCaL_i]*STATES[d]*( ALGEBRAIC[f]*(1.00000 - STATES[nca_i])+ STATES[jca]*ALGEBRAIC[fca]*STATES[nca_i])+ ALGEBRAIC[fICaLp]*CONSTANTS[PCap]*ALGEBRAIC[PhiCaL_i]*STATES[d]*( ALGEBRAIC[fp]*(1.00000 - STATES[nca_i])+ STATES[jca]*ALGEBRAIC[fcap]*STATES[nca_i]));
ALGEBRAIC[ICaL] = ALGEBRAIC[ICaL_ss]+ALGEBRAIC[ICaL_i];
ALGEBRAIC[ICaNa] = ALGEBRAIC[ICaNa_ss]+ALGEBRAIC[ICaNa_i];
ALGEBRAIC[ICaK] = ALGEBRAIC[ICaK_ss]+ALGEBRAIC[ICaK_i];
ALGEBRAIC[IpCa] = ( CONSTANTS[GpCa]*STATES[cai])/(CONSTANTS[KmCap]+STATES[cai]);
ALGEBRAIC[ICab] = ( CONSTANTS[PCab]*4.00000*ALGEBRAIC[vffrt]*( ALGEBRAIC[gamma_cai]*STATES[cai]*exp( 2.00000*ALGEBRAIC[vfrt]) -  CONSTANTS[gamma_cao]*CONSTANTS[cao]))/(exp( 2.00000*ALGEBRAIC[vfrt]) - 1.00000);
ALGEBRAIC[IClCa_junc] =  (( CONSTANTS[Fjunc]*CONSTANTS[GClCa])/(1.00000+CONSTANTS[KdClCa]/STATES[cass]))*(STATES[v] - CONSTANTS[ECl]);
ALGEBRAIC[IClCa_sl] =  (( (1.00000 - CONSTANTS[Fjunc])*CONSTANTS[GClCa])/(1.00000+CONSTANTS[KdClCa]/STATES[cai]))*(STATES[v] - CONSTANTS[ECl]);
ALGEBRAIC[IClCa] = ALGEBRAIC[IClCa_junc]+ALGEBRAIC[IClCa_sl];
ALGEBRAIC[IClb] =  CONSTANTS[GClb]*(STATES[v] - CONSTANTS[ECl]);
ALGEBRAIC[Jupnp] = ( CONSTANTS[upScale]*0.00542500*STATES[cai])/(STATES[cai]+0.000920000);
ALGEBRAIC[Jupp] = ( CONSTANTS[upScale]*2.75000*0.00542500*STATES[cai])/((STATES[cai]+0.000920000) - 0.000170000);
ALGEBRAIC[fJupp] = 1.00000/(1.00000+CONSTANTS[KmCaMK]/ALGEBRAIC[CaMKa]);
ALGEBRAIC[Jleak] = ( 0.00488250*STATES[cansr])/15.0000;
ALGEBRAIC[Jup] =  CONSTANTS[Jup_b]*(( (1.00000 - ALGEBRAIC[fJupp])*ALGEBRAIC[Jupnp]+ ALGEBRAIC[fJupp]*ALGEBRAIC[Jupp]) - ALGEBRAIC[Jleak]);
ALGEBRAIC[Bcai] = 1.00000/(1.00000+( CONSTANTS[cmdnmax]*CONSTANTS[kmcmdn])/pow(CONSTANTS[kmcmdn]+STATES[cai], 2.00000)+( CONSTANTS[trpnmax]*CONSTANTS[kmtrpn])/pow(CONSTANTS[kmtrpn]+STATES[cai], 2.00000));
ALGEBRAIC[Jtr] = (STATES[cansr] - STATES[cajsr])/60.0000;
ALGEBRAIC[Bcajsr] = 1.00000/(1.00000+( CONSTANTS[csqnmax]*CONSTANTS[kmcsqn])/pow(CONSTANTS[kmcsqn]+STATES[cajsr], 2.00000));

RATES[hL] = (ALGEBRAIC[hLss] - STATES[hL])/CONSTANTS[thL];
RATES[hLp] = (ALGEBRAIC[hLssp] - STATES[hLp])/CONSTANTS[thLp];
RATES[jca] = (ALGEBRAIC[jcass] - STATES[jca])/CONSTANTS[tjca];
RATES[m] = (ALGEBRAIC[mss] - STATES[m])/ALGEBRAIC[tm];
RATES[mL] = (ALGEBRAIC[mLss] - STATES[mL])/ALGEBRAIC[tmL];
RATES[a] = (ALGEBRAIC[ass] - STATES[a])/ALGEBRAIC[ta];
RATES[d] = (ALGEBRAIC[dss] - STATES[d])/ALGEBRAIC[td];
RATES[ff] = (ALGEBRAIC[fss] - STATES[ff])/ALGEBRAIC[tff];
RATES[fs] = (ALGEBRAIC[fss] - STATES[fs])/ALGEBRAIC[tfs];
RATES[nca_ss] =  ALGEBRAIC[anca_ss]*CONSTANTS[k2n] -  STATES[nca_ss]*ALGEBRAIC[km2n];
RATES[nca_i] =  ALGEBRAIC[anca_i]*CONSTANTS[k2n] -  STATES[nca_i]*ALGEBRAIC[km2n];
RATES[xs1] = (ALGEBRAIC[xs1ss] - STATES[xs1])/ALGEBRAIC[txs1];
RATES[ap] = (ALGEBRAIC[assp] - STATES[ap])/ALGEBRAIC[ta];
RATES[fcaf] = (ALGEBRAIC[fcass] - STATES[fcaf])/ALGEBRAIC[tfcaf];
RATES[fcas] = (ALGEBRAIC[fcass] - STATES[fcas])/ALGEBRAIC[tfcas];
RATES[ffp] = (ALGEBRAIC[fss] - STATES[ffp])/ALGEBRAIC[tffp];
RATES[xs2] = (ALGEBRAIC[xs2ss] - STATES[xs2])/ALGEBRAIC[txs2];
RATES[CaMKt] =  CONSTANTS[aCaMK]*ALGEBRAIC[CaMKb]*(ALGEBRAIC[CaMKb]+STATES[CaMKt]) -  CONSTANTS[bCaMK]*STATES[CaMKt];
RATES[h] = (ALGEBRAIC[hss] - STATES[h])/ALGEBRAIC[th];
RATES[fcafp] = (ALGEBRAIC[fcass] - STATES[fcafp])/ALGEBRAIC[tfcafp];
RATES[j] = (ALGEBRAIC[jss] - STATES[j])/ALGEBRAIC[tj];
RATES[hp] = (ALGEBRAIC[hssp] - STATES[hp])/ALGEBRAIC[th];
RATES[iF] = (ALGEBRAIC[iss] - STATES[iF])/ALGEBRAIC[tiF];
RATES[C3] =  ALGEBRAIC[beta]*STATES[C2] -  ALGEBRAIC[alpha]*STATES[C3];
RATES[C2] = ( ALGEBRAIC[alpha]*STATES[C3]+ CONSTANTS[beta_1]*STATES[C1]) -  (ALGEBRAIC[beta]+CONSTANTS[alpha_1])*STATES[C2];
RATES[jp] = (ALGEBRAIC[jss] - STATES[jp])/ALGEBRAIC[tjp];
RATES[iS] = (ALGEBRAIC[iss] - STATES[iS])/ALGEBRAIC[tiS];
RATES[O] = ( ALGEBRAIC[alpha_2]*STATES[C1]+ ALGEBRAIC[beta_i]*STATES[I]) -  (ALGEBRAIC[beta_2]+ALGEBRAIC[alpha_i])*STATES[O];
RATES[iFp] = (ALGEBRAIC[iss] - STATES[iFp])/ALGEBRAIC[tiFp];
RATES[iSp] = (ALGEBRAIC[iss] - STATES[iSp])/ALGEBRAIC[tiSp];
RATES[C1] = ( CONSTANTS[alpha_1]*STATES[C2]+ ALGEBRAIC[beta_2]*STATES[O]+ ALGEBRAIC[beta_ItoC2]*STATES[I]) -  (CONSTANTS[beta_1]+ALGEBRAIC[alpha_2]+ALGEBRAIC[alpha_C2ToI])*STATES[C1];
RATES[I] = ( ALGEBRAIC[alpha_C2ToI]*STATES[C1]+ ALGEBRAIC[alpha_i]*STATES[O]) -  (ALGEBRAIC[beta_ItoC2]+ALGEBRAIC[beta_i])*STATES[I];
RATES[Jrel_np] = (ALGEBRAIC[Jrel_inf] - STATES[Jrel_np])/ALGEBRAIC[tau_rel];
RATES[Jrel_p] = (ALGEBRAIC[Jrel_infp] - STATES[Jrel_p])/ALGEBRAIC[tau_relp];
RATES[ki] = ( - (((ALGEBRAIC[Ito]+ALGEBRAIC[IKr]+ALGEBRAIC[IKs]+ALGEBRAIC[IK1]+ALGEBRAIC[IKb]+ALGEBRAIC[I_katp]+ALGEBRAIC[Istim]) -  2.00000*ALGEBRAIC[INaK])+ALGEBRAIC[ICaK_i])*CONSTANTS[Acap])/( CONSTANTS[F]*CONSTANTS[vmyo])+( ALGEBRAIC[JdiffK]*CONSTANTS[vss])/CONSTANTS[vmyo];
RATES[kss] = ( - ALGEBRAIC[ICaK_ss]*CONSTANTS[Acap])/( CONSTANTS[F]*CONSTANTS[vss]) - ALGEBRAIC[JdiffK];
RATES[nai] = ( - (ALGEBRAIC[INa]+ALGEBRAIC[INaL]+ 3.00000*ALGEBRAIC[INaCa_i]+ALGEBRAIC[ICaNa_i]+ 3.00000*ALGEBRAIC[INaK]+ALGEBRAIC[INab])*CONSTANTS[Acap])/( CONSTANTS[F]*CONSTANTS[vmyo])+( ALGEBRAIC[JdiffNa]*CONSTANTS[vss])/CONSTANTS[vmyo];
RATES[nass] = ( - (ALGEBRAIC[ICaNa_ss]+ 3.00000*ALGEBRAIC[INaCa_ss])*CONSTANTS[Acap])/( CONSTANTS[F]*CONSTANTS[vss]) - ALGEBRAIC[JdiffNa];
RATES[cass] =  ALGEBRAIC[Bcass]*((( - (ALGEBRAIC[ICaL_ss] -  2.00000*ALGEBRAIC[INaCa_ss])*CONSTANTS[Acap])/( 2.00000*CONSTANTS[F]*CONSTANTS[vss])+( ALGEBRAIC[Jrel]*CONSTANTS[vjsr])/CONSTANTS[vss]) - ALGEBRAIC[Jdiff]);
RATES[v] = - (ALGEBRAIC[INa]+ALGEBRAIC[INaL]+ALGEBRAIC[Ito]+ALGEBRAIC[ICaL]+ALGEBRAIC[ICaNa]+ALGEBRAIC[ICaK]+ALGEBRAIC[IKr]+ALGEBRAIC[IKs]+ALGEBRAIC[IK1]+ALGEBRAIC[INaCa_i]+ALGEBRAIC[INaCa_ss]+ALGEBRAIC[INaK]+ALGEBRAIC[INab]+ALGEBRAIC[IKb]+ALGEBRAIC[IpCa]+ALGEBRAIC[ICab]+ALGEBRAIC[IClCa]+ALGEBRAIC[IClb]+ALGEBRAIC[I_katp]+ALGEBRAIC[Istim]);
RATES[cai] =  ALGEBRAIC[Bcai]*((( - ((ALGEBRAIC[ICaL_i]+ALGEBRAIC[IpCa]+ALGEBRAIC[ICab]) -  2.00000*ALGEBRAIC[INaCa_i])*CONSTANTS[Acap])/( 2.00000*CONSTANTS[F]*CONSTANTS[vmyo]) - ( ALGEBRAIC[Jup]*CONSTANTS[vnsr])/CONSTANTS[vmyo])+( ALGEBRAIC[Jdiff]*CONSTANTS[vss])/CONSTANTS[vmyo]);
RATES[cansr] = ALGEBRAIC[Jup] - ( ALGEBRAIC[Jtr]*CONSTANTS[vjsr])/CONSTANTS[vnsr];
RATES[cajsr] =  ALGEBRAIC[Bcajsr]*(ALGEBRAIC[Jtr] - ALGEBRAIC[Jrel]);
}

void Tomek_model::solveRK4(double TIME, double dt)
{
	double k1[43],k23[43];
	double yk123[43];
	int idx;


	// assuming first computeRates() have been executed
	computeRates( TIME, CONSTANTS, RATES, STATES, ALGEBRAIC );
	for( idx = 0; idx < states_size; idx++ ) {
		k1[idx] = RATES[idx];
		yk123[idx] = STATES[idx] + (k1[idx]*dt*0.5);
	}
	computeRates( TIME+(dt*0.5), CONSTANTS, RATES, yk123, ALGEBRAIC );
	for( idx = 0; idx < states_size; idx++ ) {
		k23[idx] = RATES[idx];
		yk123[idx] = STATES[idx] + (k23[idx]*dt*0.5);
	}
	computeRates( TIME+(dt*0.5), CONSTANTS, RATES, yk123, ALGEBRAIC );
  for( idx = 0; idx < states_size; idx++ ) {
    k23[idx] += RATES[idx];
    yk123[idx] = STATES[idx] + (k23[idx]*dt);
  }
  computeRates( TIME+dt, CONSTANTS, RATES, yk123, ALGEBRAIC );
	for( idx = 0; idx < states_size; idx++ ) {
		STATES[idx] += (k1[idx]+(2*k23[idx])+RATES[idx])/6. * dt;
  }


}

void Tomek_model::solveAnalytical(double dt)
{
#ifdef EULER
  STATES[v] = STATES[v] + RATES[v] * dt;
  STATES[CaMKt] = STATES[CaMKt] + RATES[CaMKt] * dt;
  STATES[cass] = STATES[cass] + RATES[cass] * dt;
  STATES[nai] = STATES[nai] + RATES[nai] * dt;
  STATES[nass] = STATES[nass] + RATES[nass] * dt;
  STATES[ki] = STATES[ki] + RATES[ki] * dt;
  STATES[kss] = STATES[kss] + RATES[kss] * dt;
  STATES[cansr] = STATES[cansr] + RATES[cansr] * dt;
  STATES[cajsr] = STATES[cajsr] + RATES[cajsr] * dt;
  STATES[cai] = STATES[cai] + RATES[cai] * dt;
  STATES[m] = STATES[m] + RATES[m] * dt;
  STATES[h] = STATES[h] + RATES[h] * dt;
  STATES[j] = STATES[j] + RATES[j] * dt;
  STATES[hp] = STATES[hp] + RATES[hp] * dt;
  STATES[jp] = STATES[jp] + RATES[jp] * dt;
  STATES[mL] = STATES[mL] + RATES[mL] * dt;
  STATES[hL] = STATES[hL] + RATES[hL] * dt;
  STATES[hLp] = STATES[hLp] + RATES[hLp] * dt;
  STATES[a] = STATES[a] + RATES[a] * dt;
  STATES[iF] = STATES[iF] + RATES[iF] * dt;
  STATES[iS] = STATES[iS] + RATES[iS] * dt;
  STATES[ap] = STATES[ap] + RATES[ap] * dt;
  STATES[iFp] = STATES[iFp] + RATES[iFp] * dt;
  STATES[iSp] = STATES[iSp] + RATES[iSp] * dt;
  STATES[d] = STATES[d] + RATES[d] * dt;
  STATES[ff] = STATES[ff] + RATES[ff] * dt;
  STATES[fs] = STATES[fs] + RATES[fs] * dt;
  STATES[fcaf] = STATES[fcaf] + RATES[fcaf] * dt;
  STATES[fcas] = STATES[fcas] + RATES[fcas] * dt;
  STATES[jca] = STATES[jca] + RATES[jca] * dt;
  STATES[ffp] = STATES[ffp] + RATES[ffp] * dt;
  STATES[fcafp] = STATES[fcafp] + RATES[fcafp] * dt;
  STATES[nca_ss] = STATES[nca_ss] + RATES[nca_ss] * dt;
  STATES[nca_i] = STATES[nca_i] + RATES[nca_i] * dt;
  STATES[O] = STATES[O] + RATES[O] * dt;
  STATES[I] = STATES[I] + RATES[I] * dt;
	STATES[C3] = STATES[C3] + RATES[C3] * dt;
	STATES[C2] = STATES[C2] + RATES[C2] * dt;
	STATES[C1] = STATES[C1] + RATES[C1] * dt;
  STATES[xs1] = STATES[xs1] + RATES[xs1] * dt;
  STATES[xs2] = STATES[xs2] + RATES[xs2] * dt;
  STATES[Jrel_np] = STATES[Jrel_np] + RATES[Jrel_np] * dt;
  STATES[Jrel_p] = STATES[Jrel_p] + RATES[Jrel_p] * dt;
#else
////==============
////Exact solution
////==============
////INa
  STATES[m] = ALGEBRAIC[mss] - (ALGEBRAIC[mss] - STATES[m]) * exp(-dt / ALGEBRAIC[tm]);
  STATES[h] = ALGEBRAIC[hss] - (ALGEBRAIC[hss] - STATES[h]) * exp(-dt / ALGEBRAIC[th]);
  STATES[j] = ALGEBRAIC[jss] - (ALGEBRAIC[jss] - STATES[j]) * exp(-dt / ALGEBRAIC[tj]);
  STATES[hp] = ALGEBRAIC[hssp] - (ALGEBRAIC[hssp] - STATES[hp]) * exp(-dt / ALGEBRAIC[th]);
  STATES[jp] = ALGEBRAIC[jss] - (ALGEBRAIC[jss] - STATES[jp]) * exp(-dt / ALGEBRAIC[tjp]);
  STATES[mL] = ALGEBRAIC[mLss] - (ALGEBRAIC[mLss] - STATES[mL]) * exp(-dt / ALGEBRAIC[tmL]);
  STATES[hL] = ALGEBRAIC[hLss] - (ALGEBRAIC[hLss] - STATES[hL]) * exp(-dt / CONSTANTS[thL]);
  STATES[hLp] = ALGEBRAIC[hLssp] - (ALGEBRAIC[hLssp] - STATES[hLp]) * exp(-dt / CONSTANTS[thLp]);
////Ito
  STATES[a] = ALGEBRAIC[ass] - (ALGEBRAIC[ass] - STATES[a]) * exp(-dt / ALGEBRAIC[ta]);
  STATES[iF] = ALGEBRAIC[iss] - (ALGEBRAIC[iss] - STATES[iF]) * exp(-dt / ALGEBRAIC[tiF]);
  STATES[iS] = ALGEBRAIC[iss] - (ALGEBRAIC[iss] - STATES[iS]) * exp(-dt / ALGEBRAIC[tiS]);
  STATES[ap] = ALGEBRAIC[assp] - (ALGEBRAIC[assp] - STATES[ap]) * exp(-dt / ALGEBRAIC[ta]);
  STATES[iFp] = ALGEBRAIC[iss] - (ALGEBRAIC[iss] - STATES[iFp]) * exp(-dt / ALGEBRAIC[tiFp]);
  STATES[iSp] = ALGEBRAIC[iss] - (ALGEBRAIC[iss] - STATES[iSp]) * exp(-dt / ALGEBRAIC[tiSp]);
////ICaL
  STATES[d] = ALGEBRAIC[dss] - (ALGEBRAIC[dss] - STATES[d]) * exp(-dt / ALGEBRAIC[td]);
  STATES[ff] = ALGEBRAIC[fss] - (ALGEBRAIC[fss] - STATES[ff]) * exp(-dt / ALGEBRAIC[tff]);
  STATES[fs] = ALGEBRAIC[fss] - (ALGEBRAIC[fss] - STATES[fs]) * exp(-dt / ALGEBRAIC[tfs]);
  STATES[fcaf] = ALGEBRAIC[fcass] - (ALGEBRAIC[fcass] - STATES[fcaf]) * exp(-dt / ALGEBRAIC[tfcaf]);
  STATES[fcas] = ALGEBRAIC[fcass] - (ALGEBRAIC[fcass] - STATES[fcas]) * exp(-dt / ALGEBRAIC[tfcas]);
  STATES[jca] = ALGEBRAIC[jcass] - (ALGEBRAIC[jcass] - STATES[jca]) * exp(- dt / CONSTANTS[tjca]);
  STATES[ffp] = ALGEBRAIC[fss] - (ALGEBRAIC[fss] - STATES[ffp]) * exp(-dt / ALGEBRAIC[tffp]);
  STATES[fcafp] = ALGEBRAIC[fcass] - (ALGEBRAIC[fcass] - STATES[fcafp]) * exp(-d / ALGEBRAIC[tfcafp]);
	STATES[nca_i] = STATES[nca_i] + RATES[nca_i]*dt;
	STATES[nca_ss] = STATES[nca_ss] + RATES[nca_ss]*dt;
//  STATES[nca_i] = ALGEBRAIC[anca_i] * CONSTANTS[k2n] / ALGEBRAIC[km2n] -
//      (ALGEBRAIC[anca_i] * CONSTANTS[k2n] / ALGEBRAIC[km2n] - STATES[nca_i]) * exp(-ALGEBRAIC[km2n] * dt);
//  STATES[nca_ss] = ALGEBRAIC[anca_ss] * CONSTANTS[k2n] / ALGEBRAIC[km2n] -
//      (ALGEBRAIC[anca_ss] * CONSTANTS[k2n] / ALGEBRAIC[km2n] - STATES[nca_ss]) * exp(-ALGEBRAIC[km2n] * dt);
////IKr
  STATES[O] = STATES[O] + RATES[O] * dt;
  STATES[I] = STATES[I] + RATES[I] * dt;
  STATES[C3] = STATES[C3] + RATES[C3] * dt;
  STATES[C2] = STATES[C2] + RATES[C2] * dt;
  STATES[C1] = STATES[C1] + RATES[C1] * dt;
////IKs
  STATES[xs1] = ALGEBRAIC[xs1ss] - (ALGEBRAIC[xs1ss] - STATES[xs1]) * exp(-dt / ALGEBRAIC[txs1]);
  STATES[xs2] = ALGEBRAIC[xs2ss] - (ALGEBRAIC[xs2ss] - STATES[xs2]) * exp(-dt / ALGEBRAIC[txs2]);
////IK1
////RyR receptors
  STATES[Jrel_np] = ALGEBRAIC[Jrel_inf] - (ALGEBRAIC[Jrel_inf] - STATES[Jrel_np]) * exp(-dt / ALGEBRAIC[tau_rel]);
  STATES[Jrel_p] = ALGEBRAIC[Jrel_infp] - (ALGEBRAIC[Jrel_infp] - STATES[Jrel_p]) * exp(-dt / ALGEBRAIC[tau_relp]);
////=============================
////Approximated solution (Euler)
////=============================
////CaMK
  STATES[CaMKt] = STATES[CaMKt] + RATES[CaMKt] * dt;
////Membrane potential
  STATES[v] = STATES[v] + RATES[v] * dt;
////Ion Concentrations and Buffers
  STATES[nai] = STATES[nai] + RATES[nai] * dt;
  STATES[nass] = STATES[nass] + RATES[nass] * dt;
  STATES[ki] = STATES[ki] + RATES[ki] * dt;
  STATES[kss] = STATES[kss] + RATES[kss] * dt;
  STATES[cai] = STATES[cai] + RATES[cai] * dt;
  STATES[cass] = STATES[cass] + RATES[cass] * dt;
  STATES[cansr] = STATES[cansr] + RATES[cansr] * dt;
  STATES[cajsr] = STATES[cajsr] + RATES[cajsr] * dt;
#endif

}


double Tomek_model::set_time_step(double TIME,
  double time_point,
  double max_time_step,
  double* CONSTANTS,
  double* RATES,
  double* STATES,
  double* ALGEBRAIC) {
  double time_step = 0.005;

  if (TIME <= time_point || (TIME - floor(TIME / CONSTANTS[BCL]) * CONSTANTS[BCL]) <= time_point) {
    //printf("TIME <= time_point ms\n");
    return time_step;
    //printf("dV = %lf, time_step = %lf\n",RATES[v] * time_step, time_step);
  }
  else {
    //printf("TIME > time_point ms\n");
    if (std::abs(RATES[v] * time_step) <= 0.2) {//Slow changes in V
        //printf("dV/dt <= 0.2\n");
        time_step = std::abs(0.8 / RATES[v]);
        //Make sure time_step is between 0.005 and max_time_step
        if (time_step < 0.005) {
            time_step = 0.005;
        }
        else if (time_step > max_time_step) {
            time_step = max_time_step;
        }
        //printf("dV = %lf, time_step = %lf\n",std::abs(RATES[v] * time_step), time_step);
    }
    else if (std::abs(RATES[v] * time_step) >= 0.8) {//Fast changes in V
        //printf("dV/dt >= 0.8\n");
        time_step = std::abs(0.2 / RATES[v]);
        while (std::abs(RATES[v] * time_step) >= 0.8 &&
               0.005 < time_step &&
               time_step < max_time_step) {
            time_step = time_step / 10.0;
            //printf("dV = %lf, time_step = %lf\n",std::abs(RATES[v] * time_step), time_step);
        }
    }
    return time_step;
  }
}

