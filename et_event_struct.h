
/* STRUCTURES */

/**
 * This structure defines an <b>Event</b> which exists in shared memory, holds data,
 * and gets passed from station to station.
 */
typedef struct et_event_t {
  struct et_event_t *next;  /**< Next event in linked list. */
  void    *tempdata;        /**< For MacOS or non mutex-sharing systems, a temp event
                                 gotten by the server thread needs its data pointer stored
                                 while the user maps the temp file and puts that pointer
                                 in pdata field (when converting the pdata pointer back to
                                 a value the ET system uses, so the server thread can
                                 unmap it from memory, grab & restore the stored value). */
  void    *pdata;           /**< Set to either <b>data</b> field pointer (shared mem),
 *                               or to temp event buffer. */
  char    *data;            /**< Pointer to shared memory data. */
  uint64_t length;          /**< Size of actual data in bytes. */
  uint64_t memsize;         /**< Total size of available data memory in bytes. */

  /* for remote events */
  uint64_t pointer;        /**< For remote events, pointer to this event in the
                                server's space (used for writing of modified events). */
  int      modify;         /**< When "getting" events from a remote client, this flag tells
                                server whether this event will be modified with the
                                intention of sending it back to the server (@ref ET_MODIFY) or
                                whether only the header will be modified and returned
                                (@ref ET_MODIFY_HEADER) or whether there'll be no modification
                                of the event (0). */
  /* ----------------- */

  int     priority;        /**< Event priority, either @ref ET_HIGH or @ref ET_LOW. */
  int     owner;           /**< Id of attachment that owns this event, else the system (-1). */
  int     temp;            /**< @ref ET_EVENT_TEMP if temporary event, else @ref ET_EVENT_NORMAL. */
  int     age;             /**< @ref ET_EVENT_NEW if it's a new event, else @ref ET_EVENT_USED
                                (new events always go to GrandCentral if user crashes). */
  int     datastatus;      /**< @ref ET_DATA_OK normally, @ref ET_DATA_CORRUPT if data corrupt,
                                @ref ET_DATA_POSSIBLY_CORRUPT if data questionable. */
  int     byteorder;       /**< Use to track the data's endianness (set to 0x04030201). */
  int     group;           /**< Group number, events are divided into groups for limiting
                                the number of events producers have access to. */
  int     place;           /**< Place number of event's relative position in shared mem starting
                                with 0 (lowest memory position) and ending with (# of events - 1). */
  int     control[ET_STATION_SELECT_INTS];  /**< Array of ints to select on for entry into station. */
  char    filename[ET_TEMPNAME_LENGTH];     /**< Filename of temp event. */
} et_event;
