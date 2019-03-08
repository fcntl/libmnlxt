#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/libmnlxt/rt_rule.h"
#include "../../include/mnlxt_tools.h"

mnlxt_rt_rule_t *mnlxt_rt_rule_new() {
	return calloc(1, sizeof(mnlxt_rt_rule_t));
}

void mnlxt_rt_rule_free(mnlxt_rt_rule_t *rule) {
	if (rule) {
		free(rule);
	}
}

void mnlxt_rt_rule_FREE(void *rule) {
	mnlxt_rt_rule_free((mnlxt_rt_rule_t *)rule);
}

int mnlxt_rt_rule_set_family(mnlxt_rt_rule_t *rule, uint8_t family) {
	int rc = -1;
	if (rule) {
		if (AF_INET == family || AF_INET6 == family) {
			if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_FAMILY)) {
				if (family == rule->family) {
					rc = 0;
				}
			} else {
				rule->family = family;
				MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_FAMILY);
				rc = 0;
			}
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_family(mnlxt_rt_rule_t *rule, uint8_t *family) {
	int rc = -1;
	if (rule && family) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_FAMILY)) {
			*family = rule->family;
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_set_src_prefix(mnlxt_rt_rule_t *rule, uint8_t prefixlen) {
	int rc = -1;
	if (rule) {
		rule->src_prefix = prefixlen;
		MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_SRC_PREFIX);
		rc = 0;
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_src_prefix(mnlxt_rt_rule_t *rule, uint8_t *prefixlen) {
	int rc = -1;
	if (rule && prefixlen) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_SRC_PREFIX)) {
			*prefixlen = rule->src_prefix;
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_set_dst_prefix(mnlxt_rt_rule_t *rule, uint8_t prefixlen) {
	int rc = -1;
	if (rule) {
		rule->dst_prefix = prefixlen;
		MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_DST_PREFIX);
		rc = 0;
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_dst_prefix(mnlxt_rt_rule_t *rule, uint8_t *prefixlen) {
	int rc = -1;
	if (rule && prefixlen) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_DST_PREFIX)) {
			*prefixlen = rule->dst_prefix;
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_set_src(mnlxt_rt_rule_t *rule, uint8_t family, inet_addr_t *buf) {
	int rc = -1;
	if (rule && buf) {
		rc = mnlxt_rt_rule_set_family(rule, family);
		if (0 == rc) {
			memcpy(&rule->src, buf, (family == AF_INET6 ? sizeof(struct in6_addr) : sizeof(struct in_addr)));
			MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_SRC);
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_src(mnlxt_rt_rule_t *rule, uint8_t *family, inet_addr_t **buf) {
	int rc = -1;
	if (rule && buf) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_SRC)) {
			*buf = &rule->src;
			if (family) {
				*family = rule->family;
			}
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_set_dst(mnlxt_rt_rule_t *rule, uint8_t family, inet_addr_t *buf) {
	int rc = -1;
	if (rule && buf) {
		rc = mnlxt_rt_rule_set_family(rule, family);
		if (0 == rc) {
			memcpy(&rule->dst, buf, (family == AF_INET6 ? sizeof(struct in6_addr) : sizeof(struct in_addr)));
			MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_DST);
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_dst(mnlxt_rt_rule_t *rule, uint8_t *family, inet_addr_t **buf) {
	int rc = -1;
	if (rule && buf) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_DST)) {
			*buf = &rule->dst;
			if (family) {
				*family = rule->family;
			}
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_set_table(mnlxt_rt_rule_t *rule, uint8_t table) {
	int rc = -1;
	if (rule) {
		rule->table = table;
		MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_TABLE);
		rc = 0;
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_table(mnlxt_rt_rule_t *rule, uint8_t *table) {
	int rc = -1;
	if (rule && table) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_TABLE)) {
			*table = rule->table;
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_set_action(mnlxt_rt_rule_t *rule, uint8_t action) {
	int rc = -1;
	if (rule) {
		rule->action = action;
		MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_ACTION);
		rc = 0;
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_action(mnlxt_rt_rule_t *rule, uint8_t *action) {
	int rc = -1;
	if (rule && action) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_ACTION)) {
			*action = rule->action;
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_set_tos(mnlxt_rt_rule_t *rule, uint8_t tos) {
	int rc = -1;
	if (rule) {
		rule->tos = tos;
		MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_TOS);
		rc = 0;
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_tos(mnlxt_rt_rule_t *rule, uint8_t *tos) {
	int rc = -1;
	if (rule && tos) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_TOS)) {
			*tos = rule->tos;
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_set_priority(mnlxt_rt_rule_t *rule, uint32_t priority) {
	int rc = -1;
	if (rule) {
		rule->priority = priority;
		MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_PRIORITY);
		rc = 0;
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_priority(mnlxt_rt_rule_t *rule, uint32_t *priority) {
	int rc = -1;
	if (rule && priority) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_PRIORITY)) {
			*priority = rule->priority;
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_set_iif_name(mnlxt_rt_rule_t *rule, const char *iif_name) {
	int rc = -1;
	if (rule && iif_name) {
		rule->iif_name = strdup(iif_name);
		if (rule->iif_name) {
			rc = 0;
			MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_IIFNAME);
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_iif_name(mnlxt_rt_rule_t *rule, char **iif_name) {
	int rc = -1;
	if (rule && iif_name) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_IIFNAME) && rule->iif_name) {
			*iif_name = rule->iif_name;
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_set_oif_name(mnlxt_rt_rule_t *rule, const char *oif_name) {
	int rc = -1;
	if (rule && oif_name) {
		rule->oif_name = strdup(oif_name);
		if (rule->oif_name) {
			rc = 0;
			MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_OIFNAME);
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_oif_name(mnlxt_rt_rule_t *rule, char **oif_name) {
	int rc = -1;
	if (rule && oif_name) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_OIFNAME) && rule->oif_name) {
			*oif_name = rule->oif_name;
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_set_fwmark(mnlxt_rt_rule_t *rule, uint32_t fwmark) {
	int rc = -1;
	if (rule) {
		rule->fwmark = fwmark;
		MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_FWMARK);
		rc = 0;
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_fwmark(mnlxt_rt_rule_t *rule, uint32_t *fwmark) {
	int rc = -1;
	if (rule && fwmark) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_FWMARK)) {
			*fwmark = rule->fwmark;
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_set_fwmask(mnlxt_rt_rule_t *rule, uint32_t fwmask) {
	int rc = -1;
	if (rule) {
		rule->fwmask = fwmask;
		MNLXT_SET_PROP_FLAG(rule, MNLXT_RT_RULE_FWMASK);
		rc = 0;
	} else {
		errno = EINVAL;
	}
	return rc;
}

int mnlxt_rt_rule_get_fwmask(mnlxt_rt_rule_t *rule, uint32_t *fwmask) {
	int rc = -1;
	if (rule && fwmask) {
		if (MNLXT_GET_PROP_FLAG(rule, MNLXT_RT_RULE_FWMASK)) {
			*fwmask = rule->fwmask;
			rc = 0;
		} else {
			rc = 1;
		}
	} else {
		errno = EINVAL;
	}
	return rc;
}