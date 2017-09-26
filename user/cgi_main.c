#include <esp8266.h>
#include <httpd.h>
#include <esp_sdk_ver.h>
#include <httpdespfs.h>

#include "cgi_main.h"
#include "screen.h"
#include "version.h"
#include "helpers.h"

/**
 * Main page template substitution
 *
 * @param connData
 * @param token
 * @param arg
 * @return
 */
httpd_cgi_state ICACHE_FLASH_ATTR tplScreen(HttpdConnData *connData, char *token, void **arg)
{
	if (token == NULL) {
		// Release data object
		return HTTPD_CGI_DONE;
	}

	char buff[150];

	if (streq(token, "labels_seq")) {
		screenSerializeLabelsToBuffer(buff, 150);
		tplSend(connData, buff, -1);
	}
	else if (streq(token, "theme")) {
		sprintf(buff, "%d", termconf->theme);
		tplSend(connData, buff, -1);
	}
	else if (streq(token, "want_all_fn")) {
		sprintf(buff, "%d", termconf->want_all_fn);
		tplSend(connData, buff, -1);
	}
	else if (streq(token, "default_fg")) {
		sprintf(buff, "%d", termconf->default_fg);
		tplSend(connData, buff, -1);
	}
	else if (streq(token, "default_bg")) {
		sprintf(buff, "%d", termconf->default_bg);
		tplSend(connData, buff, -1);
	}

	return HTTPD_CGI_DONE;
}

/** "About" page */
httpd_cgi_state ICACHE_FLASH_ATTR
tplAbout(HttpdConnData *connData, char *token, void **arg)
{
	if (token == NULL) return HTTPD_CGI_DONE;

	if (streq(token, "vers_fw")) {
		tplSend(connData, FIRMWARE_VERSION, -1);
	}
	else if (streq(token, "date")) {
		tplSend(connData, __DATE__, -1);
	}
	else if (streq(token, "time")) {
		tplSend(connData, __TIME__" "__TIMEZONE__, -1);
	}
	else if (streq(token, "vers_httpd")) {
		tplSend(connData, httpdGetVersion(), -1);
	}
	else if (streq(token, "vers_sdk")) {
		//tplSend(connData, STR(ESP_SDK_VERSION), -1);
		tplSend(connData, system_get_sdk_version(), -1);
	}
	else if (streq(token, "hash_backend")) {
		tplSend(connData, GIT_HASH_BACKEND, -1);
	}
	else if (streq(token, "hash_frontend")) {
		tplSend(connData, GIT_HASH_FRONTEND, -1);
	}
	else if (streq(token, "githubrepo")) {
		tplSend(connData, TERMINAL_GITHUB_REPO, -1);
	}
	else if (streq(token, "githubrepo_front")) {
		tplSend(connData, TERMINAL_GITHUB_REPO_FRONT, -1);
	}

	return HTTPD_CGI_DONE;
}
