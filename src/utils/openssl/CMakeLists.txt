#project( openssl )
#cmake_minimum_required( VERSION 2.8.3 )

include(CMakeParseArguments)
add_definitions( -DOPENSSL_NO_ASM )

if( WIN32 AND NOT CYGWIN )
  add_definitions( -DOPENSSL_SYSNAME_WIN32 )
  add_definitions( -DWIN32_LEAN_AND_MEAN )

  # avoid conflict: ocsp.h and wincrypt.h
  add_definitions( -D_WINDLL )

endif()

if( MINGW )
  set( CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all" )
endif()

# add_submodule
# TARGET 
# PATH
# FILES
function(add_submodule) 
	cmake_parse_arguments(IN "" "TARGET;PATH" "FILES" ${ARGN}) 
	foreach( name ${IN_FILES}) 
		set(LIB_SRCS ${IN_PATH}/${name} ${LIB_SRCS})		
	endforeach(name)
	set(${IN_TARGET}_SRCS ${LIB_SRCS} PARENT_SCOPE)
endfunction(add_submodule)

set(CRYPTO_PATH crypto)
set(SSL_PATH ssl)
#set(APP_PATH ${PROJECT_SOURCE_DIR}/app)

include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	include
	.	
	${CRYPTO_PATH}/include 
	${CRYPTO_PATH}/include/openssl
	${CRYPTO_PATH}/asn1/
	${CRYPTO_PATH}/evp
	${CRYPTO_PATH}/modes
	${CRYPTO_PATH}
	${SSL_PATH}
   	)

file(READ config/opensslconf.h.in CONF)
string( REPLACE "#undef OPENSSL_EXPORT_VAR_AS_FUNCTION" "#cmakedefine OPENSSL_EXPORT_VAR_AS_FUNCTION"
   CONF "${CONF}" )

set(CONF "
#define OPENSSL_NO_GMP
#define OPENSSL_NO_JPAKE
#define OPENSSL_NO_KRB5
#define OPENSSL_NO_MD2
#define OPENSSL_NO_RC5
#define OPENSSL_NO_RFC3779
#define OPENSSL_NO_STORE
#define OPENSSL_NO_DYNAMIC_ENGINE
#define OPENSSL_NO_SCTP
#define OPENSSL_NO_EC_NISTP_64_GCC_128
${CONF}" )

file( WRITE ${CMAKE_CURRENT_BINARY_DIR}/opensslconf.h.cmake "${CONF}" )
configure_file ( config/buildinf.h.cmake buildinf.h )

if( WIN32 AND MINGW AND NOT CYGWIN )
  set( OPENSSL_EXPORT_VAR_AS_FUNCTION true )
endif()
configure_file( ${CMAKE_CURRENT_BINARY_DIR}/opensslconf.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/openssl/opensslconf.h )

set(CRYPTO_SRCS ${CRYPTO_PATH}/cryptlib.c
	${CRYPTO_PATH}/mem.c
	${CRYPTO_PATH}/mem_clr.c
	${CRYPTO_PATH}/mem_dbg.c
	${CRYPTO_PATH}/cversion.c
	${CRYPTO_PATH}/ex_data.c
	${CRYPTO_PATH}/cpt_err.c
	${CRYPTO_PATH}/ebcdic.c
	${CRYPTO_PATH}/uid.c
	${CRYPTO_PATH}/o_time.c
	${CRYPTO_PATH}/o_dir.c
	${CRYPTO_PATH}/o_str.c
	${CRYPTO_PATH}/o_init.c)
if(WIN32 AND NOT CYGWIN) 
	set_property(SOURCE ../engines/e_capi.c APPEND PROPERTY COMPILE_DEFINITIONS HEADER_OCSP_H)
endif(WIN32 AND NOT CYGWIN)


add_submodule(TARGET ENGINES_EX PATH engines FILES e_4758cca.c e_aep.c e_atalla.c e_cswift.c e_gmp.c e_chil.c
	e_nuron.c e_sureware.c e_ubsec.c e_padlock.c e_capi.c)
add_submodule(TARGET CC_GOST_EX PATH engines/ccgost  FILES e_gost_err.c gost2001.c gost2001_keyx.c gost89.c
	gost94_keyx.c gost_ameth.c gost_asn1.c gost_crypt.c gost_ctl.c gost_eng.c gosthash.c
	gost_keywrap.c gost_md.c gost_params.c gost_pmeth.c gost_sign.c)

set(CRYPTO_SRCS ${CRYPTO_SRCS} ${ENGINES_EX_SRCS} ${CC_GOST_EX_SRCS})
add_submodule(TARGET AES PATH ${CRYPTO_PATH}/aes FILES aes_core.c aes_misc.c aes_ecb.c
   	aes_cbc.c aes_cfb.c aes_ofb.c aes_ctr.c aes_ige.c aes_wrap.c)
add_submodule(TARGET ASN PATH ${CRYPTO_PATH}/asn1 FILES a_object.c a_bitstr.c a_utctm.c
   	a_gentm.c a_time.c a_int.c a_octet.c a_print.c a_type.c a_set.c a_dup.c a_d2i_fp.c 
	a_i2d_fp.c a_enum.c a_utf8.c a_sign.c a_digest.c a_verify.c a_mbstr.c a_strex.c x_algor.c 
	x_val.c x_pubkey.c x_sig.c x_req.c x_attrib.c x_bignum.c x_long.c x_name.c x_x509.c 
	x_x509a.c x_crl.c x_info.c x_spki.c nsseq.c x_nx509.c d2i_pu.c d2i_pr.c i2d_pu.c 
	i2d_pr.c t_req.c t_x509.c t_x509a.c t_crl.c t_pkey.c t_spki.c t_bitst.c tasn_new.c 
	tasn_fre.c tasn_enc.c tasn_dec.c tasn_utl.c tasn_typ.c tasn_prn.c ameth_lib.c f_int.c 
	f_string.c n_pkey.c f_enum.c x_pkey.c a_bool.c x_exten.c bio_asn1.c bio_ndef.c 
   	asn_mime.c asn1_gen.c asn1_par.c asn1_lib.c asn1_err.c a_bytes.c a_strnid.c evp_asn1.c 
	asn_pack.c p5_pbe.c	p5_pbev2.c p8_pkey.c asn_moid.c)
add_submodule(TARGET BF PATH ${CRYPTO_PATH}/bf FILES bf_skey.c bf_ecb.c bf_enc.c bf_cfb64.c bf_ofb64.c)
add_submodule(TARGET BIO PATH ${CRYPTO_PATH}/bio FILES bio_lib.c bio_cb.c bio_err.c bss_mem.c bss_null.c 
	bss_fd.c bss_file.c bss_sock.c bss_conn.c bf_null.c bf_buff.c b_print.c b_dump.c b_sock.c bss_acpt.c
	bf_nbio.c bss_log.c bss_bio.c bss_dgram.c)
add_submodule(TARGET BN PATH ${CRYPTO_PATH}/bn FILES bn_add.c bn_div.c bn_exp.c bn_lib.c bn_ctx.c bn_mul.c bn_mod.c
	bn_print.c bn_rand.c bn_shift.c bn_word.c bn_blind.c bn_kron.c bn_sqrt.c bn_gcd.c
	bn_prime.c bn_err.c bn_sqr.c bn_asm.c bn_recp.c bn_mont.c bn_mpi.c bn_exp2.c bn_gf2m.c
	bn_nist.c bn_depr.c bn_const.c)
add_submodule(TARGET BUFFER PATH ${CRYPTO_PATH}/buffer FILES buffer.c buf_err.c buf_str.c)

#NOT USE
add_submodule(TARGET CAMELLIA PATH ${CRYPTO_PATH}/camellia FILES camellia.c cmll_misc.c cmll_ecb.c cmll_cbc.c cmll_ofb.c
	cmll_cfb.c cmll_ctr.c cmll_utl.c)
add_submodule(TARGET CAST  PATH ${CRYPTO_PATH}/cast FILES c_skey.c c_ecb.c c_enc.c c_cfb64.c c_ofb64.c)
add_submodule(TARGET CMAC PATH ${CRYPTO_PATH}/cmac FILES cm_ameth.c cm_pmeth.c cmac.c)
add_submodule(TARGET CMS PATH ${CRYPTO_PATH}/cms FILES cms_lib.c cms_asn1.c cms_att.c cms_io.c cms_smime.c cms_err.c
	cms_sd.c cms_dd.c cms_cd.c cms_env.c cms_enc.c cms_ess.c cms_pwri.c)
add_submodule(TARGET ENGINE PATH ${CRYPTO_PATH}/engine FILES eng_err.c eng_lib.c eng_list.c eng_init.c eng_ctrl.c eng_table.c
	eng_pkey.c eng_fat.c eng_all.c tb_rsa.c tb_dsa.c tb_ecdsa.c tb_dh.c tb_ecdh.c tb_rand.c
	tb_store.c tb_cipher.c tb_digest.c tb_pkmeth.c tb_asnmth.c eng_openssl.c eng_cnf.c
	eng_dyn.c eng_cryptodev.c eng_rdrand.c eng_rsax.c)
add_submodule(TARGET IDEA PATH ${CRYPTO_PATH}/idea FILES i_cbc.c i_cfb64.c i_ofb64.c i_ecb.c i_skey.c)
add_submodule(TARGET SEED PATH ${CRYPTO_PATH}/seed FILES seed.c seed_ecb.c seed_cbc.c seed_cfb.c seed_ofb.c)
add_submodule(TARGET SRP PATH ${CRYPTO_PATH}/srp FILES srp_lib.c srp_vfy.c)
add_submodule(TARGET WHRLPOOL PATH ${CRYPTO_PATH}/whrlpool FILES wp_dgst.c wp_block.c)
add_submodule(TARGET TS PATH ${CRYPTO_PATH}/ts FILES ts_err.c ts_req_utils.c ts_req_print.c ts_rsp_utils.c ts_rsp_print.c
	ts_rsp_sign.c ts_rsp_verify.c ts_verify_ctx.c ts_lib.c ts_conf.c ts_asn1.c	)
add_submodule(TARGET MDC2 PATH ${CRYPTO_PATH}/mdc2 FILES mdc2dgst.c mdc2_one.c)
add_submodule(TARGET PQUEUE PATH ${CRYPTO_PATH}/pqueue FILES pqueue.c)

set(CRYPTO_SRCS ${CRYPTO_SRCS} ${PQUEUE_SRCS} ${CAMELLIA_SRCS} ${CAST_SRCS} ${CMAC_SRCS} ${CMS_SRCS} ${ENGINE_SRCS} ${IDEA_SRCS} ${SEED_SRCS} ${SRP_SRCS} ${WHRLPOOL_SRCS} ${TS_SRCS} ${MDC2_SRCS} )
# NOT USE

add_submodule(TARGET COMP PATH ${CRYPTO_PATH}/comp FILES comp_lib.c comp_err.c c_rle.c c_zlib.c)
add_submodule(TARGET CONF PATH ${CRYPTO_PATH}/conf FILES conf_err.c conf_lib.c conf_api.c conf_def.c conf_mod.c conf_mall.c
	conf_sap.c)
add_submodule(TARGET DES PATH ${CRYPTO_PATH}/des FILES cbc_cksm.c cbc_enc.c cfb64enc.c cfb_enc.c ecb3_enc.c ecb_enc.c
	enc_read.c enc_writ.c fcrypt.c ofb64enc.c ofb_enc.c pcbc_enc.c qud_cksm.c rand_key.c
	rpc_enc.c set_key.c des_enc.c fcrypt_b.c xcbc_enc.c str2key.c cfb64ede.c ofb64ede.c
	ede_cbcm_enc.c des_old.c des_old2.c read2pwd.c)
add_submodule(TARGET DH PATH ${CRYPTO_PATH}/dh FILES dh_asn1.c dh_gen.c dh_key.c dh_lib.c dh_check.c dh_err.c dh_depr.c
	dh_ameth.c dh_pmeth.c dh_prn.c)
add_submodule(TARGET DSA PATH ${CRYPTO_PATH}/dsa FILES dsa_gen.c dsa_key.c dsa_lib.c dsa_asn1.c dsa_vrf.c dsa_sign.c
	dsa_err.c dsa_ossl.c dsa_depr.c dsa_ameth.c dsa_pmeth.c dsa_prn.c)
add_submodule(TARGET DSO PATH ${CRYPTO_PATH}/dso FILES dso_dl.c dso_dlfcn.c dso_err.c dso_lib.c dso_null.c dso_openssl.c
	dso_win32.c dso_vms.c dso_beos.c)
add_submodule(TARGET EC PATH ${CRYPTO_PATH}/ec FILES ec_lib.c ecp_smpl.c ecp_mont.c ecp_nist.c ec_cvt.c ec_mult.c ec_err.c
	ec_curve.c ec_check.c ec_print.c ec_asn1.c ec_key.c ec2_smpl.c ec2_mult.c ec_ameth.c
	ec_oct.c ec_pmeth.c eck_prn.c ecp_oct.c ec2_oct.c)
add_submodule(TARGET ECDH PATH ${CRYPTO_PATH}/ecdh FILES ech_lib.c ech_ossl.c ech_key.c ech_err.c)
add_submodule(TARGET ECDSA PATH  ${CRYPTO_PATH}/ecdsa FILES ecs_lib.c ecs_asn1.c ecs_ossl.c ecs_sign.c ecs_vrf.c ecs_err.c)
add_submodule(TARGET ERR PATH ${CRYPTO_PATH}/err FILES err.c err_all.c err_prn.c)
add_submodule(TARGET EVP PATH ${CRYPTO_PATH}/evp FILES encode.c digest.c evp_enc.c evp_key.c evp_acnf.c e_des.c e_bf.c
	e_idea.c e_des3.c e_camellia.c e_rc4.c e_aes.c names.c e_seed.c e_xcbc_d.c e_rc2.c
	e_cast.c e_rc5.c m_null.c m_md2.c m_md4.c m_md5.c m_sha.c m_sha1.c m_wp.c m_dss.c
	m_dss1.c m_mdc2.c m_ripemd.c m_ecdsa.c p_open.c p_seal.c p_sign.c p_verify.c p_lib.c
	p_enc.c p_dec.c bio_md.c bio_b64.c bio_enc.c evp_err.c e_null.c c_all.c c_allc.c
	c_alld.c evp_lib.c bio_ok.c evp_pkey.c evp_pbe.c p5_crpt.c p5_crpt2.c e_old.c pmeth_lib.c
	pmeth_fn.c pmeth_gn.c m_sigver.c evp_cnf.c e_rc4_hmac_md5.c e_aes_cbc_hmac_sha1.c
	)
add_submodule(TARGET HMAC PATH ${CRYPTO_PATH}/hmac FILES hmac.c hm_ameth.c hm_pmeth.c)
add_submodule(TARGET KRB5 PATH ${CRYPTO_PATH}/krb5 FILES krb5_asn.c )
add_submodule(TARGET LHASH PATH ${CRYPTO_PATH}/lhash FILES lhash.c lh_stats.c)
add_submodule(TARGET MD4 PATH ${CRYPTO_PATH}/md4 FILES md4_dgst.c md4_one.c)
add_submodule(TARGET MD5 PATH ${CRYPTO_PATH}/md5 FILES md5_dgst.c md5_one.c)
add_submodule(TARGET MODES PATH ${CRYPTO_PATH}/modes FILES cbc128.c ccm128.c ctr128.c cts128.c cfb128.c
   	gcm128.c ofb128.c xts128.c)
add_submodule(TARGET OBJ PATH ${CRYPTO_PATH}/objects FILES o_names.c obj_dat.c obj_lib.c obj_err.c obj_xref.c)
add_submodule(TARGET OCSP PATH ${CRYPTO_PATH}/ocsp FILES ocsp_asn.c ocsp_ext.c ocsp_ht.c ocsp_lib.c ocsp_cl.c ocsp_srv.c
	ocsp_prn.c ocsp_vfy.c ocsp_err.c)
add_submodule(TARGET PEM PATH ${CRYPTO_PATH}/pem FILES pem_sign.c pem_seal.c pem_info.c pem_lib.c pem_all.c pem_err.c
	pem_x509.c pem_xaux.c pem_oth.c pem_pk8.c pem_pkey.c pvkfmt.c)
add_submodule(TARGET PKCS12 PATH ${CRYPTO_PATH}/pkcs12 FILES p12_add.c p12_asn.c p12_attr.c p12_crpt.c p12_crt.c p12_decr.c
	p12_init.c p12_key.c p12_kiss.c p12_mutl.c p12_utl.c p12_npas.c pk12err.c p12_p8d.c p12_p8e.c)
add_submodule(TARGET PKCS7 PATH ${CRYPTO_PATH}/pkcs7 FILES pk7_asn1.c pk7_lib.c pkcs7err.c pk7_doit.c pk7_smime.c pk7_attr.c
	pk7_mime.c bio_pk7.c )
add_submodule(TARGET RAND PATH ${CRYPTO_PATH}/rand FILES md_rand.c randfile.c rand_lib.c rand_err.c rand_egd.c rand_win.c
	rand_unix.c rand_os2.c rand_nw.c)
add_submodule(TARGET RC2 PATH ${CRYPTO_PATH}/rc2 FILES rc2_ecb.c rc2_skey.c rc2_cbc.c rc2cfb64.c rc2ofb64.c)

add_submodule(TARGET RC4 PATH ${CRYPTO_PATH}/rc4 FILES rc4_skey.c rc4_enc.c rc4_utl.c)
add_submodule(TARGET RIPEMD PATH ${CRYPTO_PATH}/ripemd FILES rmd_dgst.c rmd_one.c)
add_submodule(TARGET RSA PATH ${CRYPTO_PATH}/rsa FILES rsa_eay.c rsa_gen.c rsa_lib.c rsa_sign.c rsa_saos.c rsa_err.c
	rsa_pk1.c rsa_ssl.c rsa_none.c rsa_oaep.c rsa_chk.c rsa_null.c rsa_pss.c rsa_x931.c
	rsa_asn1.c rsa_depr.c rsa_ameth.c rsa_prn.c rsa_pmeth.c rsa_crpt.c )
add_submodule(TARGET SHA PATH ${CRYPTO_PATH}/sha FILES sha_dgst.c sha1dgst.c sha_one.c sha1_one.c sha256.c sha512.c)
add_submodule(TARGET STACK PATH ${CRYPTO_PATH}/stack FILES stack.c)
add_submodule(TARGET TXT_DB PATH ${CRYPTO_PATH}/txt_db FILES txt_db.c)
add_submodule(TARGET UI PATH ${CRYPTO_PATH}/ui FILES ui_err.c ui_lib.c ui_openssl.c ui_util.c ui_compat.c )
add_submodule(TARGET X509 PATH ${CRYPTO_PATH}/x509 FILES x509_def.c x509_d2.c x509_r2x.c x509_cmp.c x509_obj.c x509_req.c
	x509spki.c x509_vfy.c x509_set.c x509cset.c x509rset.c x509_err.c x509name.c x509_v3.c
	x509_ext.c x509_att.c x509type.c x509_lu.c x_all.c x509_txt.c x509_trs.c by_file.c
	by_dir.c x509_vpm.c)
add_submodule(TARGET X509V3 PATH ${CRYPTO_PATH}/x509v3 FILES v3_bcons.c v3_bitst.c v3_conf.c v3_extku.c v3_ia5.c v3_lib.c
	v3_prn.c v3_utl.c v3err.c v3_genn.c v3_alt.c v3_skey.c v3_akey.c v3_pku.c v3_int.c
	v3_enum.c v3_sxnet.c v3_cpols.c v3_crld.c v3_purp.c v3_info.c v3_ocsp.c v3_akeya.c
	v3_pmaps.c v3_pcons.c v3_ncons.c v3_pcia.c v3_pci.c pcy_cache.c pcy_node.c pcy_data.c
	pcy_map.c pcy_tree.c pcy_lib.c v3_asid.c v3_addr.c)

set(CRYPTO_SRCS ${CRYPTO_SRCS} ${AES_SRCS} ${ASN_SRCS} ${BF_SRCS} ${BIO_SRCS} ${BN_SRCS} ${BUFFER_SRCS} ${COMP_SRCS} ${CONF_SRCS} ${DES_SRCS} ${DH_SRCS} ${DSA_SRCS} ${DSO_SRCS} ${EC_SRCS} ${ECDH_SRCS} ${ECDSA_SRCS} ${ERR_SRCS} ${EVP_SRCS} ${HMAC_SRCS} ${KRB5_SRCS} ${LHASH_SRCS} ${MD4_SRCS} ${MD5_SRCS} ${MODES_SRCS} ${OBJ_SRCS} ${OCSP_SRCS} ${PEM_SRCS} ${PKCS12_SRCS} ${PKCS7_SRCS} ${RAND_SRCS} ${RC2_SRCS} ${RC4_SRCS} ${RIPEMD_SRCS} ${RSA_SRCS} ${SHA_SRCS} ${STACK_SRCS} ${TXT_DB_SRCS} ${UI_SRCS} ${X509_SRCS} ${X509V3_SRCS})

add_submodule(TARGET SSL PATH ${SSL_PATH} FILES s2_meth.c s2_srvr.c s2_clnt.c s2_lib.c s2_enc.c s2_pkt.c s3_meth.c s3_srvr.c
	s3_clnt.c s3_lib.c s3_enc.c s3_pkt.c s3_both.c s23_meth.c s23_srvr.c s23_clnt.c
	s23_lib.c s23_pkt.c t1_meth.c t1_srvr.c t1_clnt.c t1_lib.c t1_enc.c d1_meth.c d1_srvr.c
	d1_clnt.c d1_lib.c d1_pkt.c d1_both.c d1_enc.c ssl_lib.c ssl_err2.c ssl_cert.c
	ssl_sess.c ssl_ciph.c ssl_stat.c ssl_rsa.c ssl_asn1.c ssl_txt.c ssl_algs.c bio_ssl.c
	ssl_err.c kssl.c t1_reneg.c tls_srp.c s3_cbc.c d1_srtp.c)

set(CRYPTO_LIB crypto)
add_library(${CRYPTO_LIB} SHARED ${CRYPTO_SRCS})

set(SSL_LIB ssl)
add_library(${SSL_LIB} SHARED ${SSL_SRCS})
target_link_libraries(${SSL_LIB} ${CRYPTO_LIB})

if(WIN32 AND NOT CYGWIN) 
	target_link_libraries(${CRYPTO_LIB} ws2_32 crypt32)
endif()

set_property(GLOBAL PROPERTY SSL_LIB "${SSL_LIB}")

#foreach(name ${CRYPTO_SRCS}) 
#	message("file : ${name} ")
#endforeach(name)


