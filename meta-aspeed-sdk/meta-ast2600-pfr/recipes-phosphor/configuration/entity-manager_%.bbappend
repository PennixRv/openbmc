FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI:append = "  file://ast2600-dcscm.json"
SRC_URI:append = "  file://blacklist.json"

do_install:append() {
     install -d ${D}/usr/share/entity-manager/configurations
     install -m 0444 ${WORKDIR}/ast2600-dcscm.json ${D}/usr/share/entity-manager/configurations
     install -m 0444 ${WORKDIR}/blacklist.json -D -t ${D}${datadir}/entity-manager
     rm -f ${D}${datadir}/entity-manager/configurations/ast2600-evb.json
}
