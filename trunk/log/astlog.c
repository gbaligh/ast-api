
/**
 *  \fn astman_add_param(char *buf, int buflen, char *header, char *value)
 *  \brief  Add a new parameter to the Command
 *  \param  buf
 *  \param  buflen
 *  \param  header
 *  \param  value
 *  \return Number of wrote characters into the buf
 */
void astman_dump_message(struct message *m)
{
  int x;
  astlog(ASTLOG_INFO, "< Received:\n");
  for (x=0;x<m->hdrcount;x++) {
    astlog(ASTLOG_INFO, "< %s\n", m->headers[x]);
  }
  astlog(ASTLOG_INFO, "\n");
}
/**
 *  \fn astman_add_param(char *buf, int buflen, char *header, char *value)
 *  \brief  Add a new parameter to the Command
 *  \param  buf
 *  \param  buflen
 *  \param  header
 *  \param  value
 *  \return Number of wrote characters into the buf
 */
static void astman_dump_out_message(char *message)
{
  char *s;
  astlog(ASTLOG_INFO, "> Transmitted:\n");
  //  printf("> Action: %s\n", action);
  while(*message) {
    s = message;
    while(*s && (*s != '\r')) s++;
    if (!*s)
      break;
    *s = '\0';
    astlog(ASTLOG_INFO, "> %s\n", message);
    s+=2;
    message = s;
  }
  astlog(ASTLOG_INFO, "\n");
}
