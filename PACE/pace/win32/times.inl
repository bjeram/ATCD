/* $Id$ -*- C -*-

 * =============================================================================
 *
 * = LIBRARY
 *    pace
 *
 * = FILENAME
 *    pace/win32/times.inl
 *
 * = AUTHOR
 *    Luther Baker
 *
 * ============================================================================= */

#if (PACE_HAS_POSIX_MP_UOF)
PACE_INLINE
pace_clock_t
pace_times (struct tms * buffer)
{
  return times (buffer);
}
#endif /* PACE_HAS_POSIX_MP_UOF */
