// -*- Mode: C++; tab-width:2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi:tw=80:et:ts=2:sts=2
//
// -----------------------------------------------------------------------
//
// This file is part of RLVM, a RealLive virtual machine clone.
//
// -----------------------------------------------------------------------
//
// Copyright (C) 2008 Elliot Glaysher
//  
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//  
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//  
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//  
// -----------------------------------------------------------------------

#ifndef __SDLMusic_hpp__
#define __SDLMusic_hpp__

#include "Systems/Base/SoundSystem.hpp"

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

#include <SDL/SDL_mixer.h>

#include "wavfile.h"

/** 
 * Encapsulates access to a 
 *
 * @section SDLMusic_WHY The "Why" of this system.
 * 
 * This system is the way it is for a good reason. The first shot of
 * this had two subclasses of SDLMusic, one which implemented formats
 * (ogg, mp3, wav, etc.), the other which mucks about with SDL_Mixer's
 * Mix_HookMusic() method for just nwa files.
 *
 * Jagarl used Mix_HookMusic along with his own loaders for all file
 * formats. He did this because in the \#DSTRACK definition, there is
 * a point in the file where you loop back to when the track
 * ends. This is why ripped NWA files end so abruptly if you play them
 * in a music player: they're designed to be looped forever and you
 * can't get that effect with built ins.
 * 
 * So instead of taking just jagarl's nwatowav.cc, I'm also stealing
 * wavfile.{cc,h}, and some binding code.
 */
class SDLMusic : public boost::noncopyable,
                 public boost::enable_shared_from_this<SDLMusic>
{
private:
  /// Underlying data stream. (These classes stolen from xclannad.)
  WAVFILE* m_file;

  /// The underlying track information
  const SoundSystem::DSTrack& m_track;

  /// No idea.
  int m_fadeCount;

  /// Number of milliseconds left to fade out the 
  int m_fadetimeTotal;

  /// The starting loop point.
  int m_loopPoint;

  /// The currently playing track.
  static boost::shared_ptr<SDLMusic> s_currentlyPlaying;

  /** 
   * Callback function to Mix_HookMusic.
   * 
   * @param udata Closure; points to an instance of MusicImpl to be
   *              used as a this pointer.
   * @param stream Audio buffer to be filled with len bytes
   * @param len Number of bytes to copy to the audio buffer stream
   *
   * @note This function was ripped off almost verbatim from xclannad!
   *       Specifically the static method WavChunk::callback in
   *       music2/music.cc.
   */
  static void MixMusic(void *udata, Uint8 *stream, int len);

  /** 
   * Builds an SDLMusic object.
   * 
   * @param track Track data (Name, looping, et cetera)
   * @param wav Generic access to music data; this is one of
   *            xclannad's objects.
   */
  SDLMusic(const SoundSystem::DSTrack& track, WAVFILE* wav);

  /** 
   * Initializes the m_loopPoint variable to either the looping point
   * for the track or a value which signals that we don't want to
   * loop.
   * 
   * @param loop Whether we should loop endlessly.
   */
  void setLoopPoint(bool loop);

public:
  ~SDLMusic();

  // TODO: Now that I understand wtf is going on, redo this part here.
  void play(bool loop);
  void stop();
  void fadeIn(bool loop, int fadeInMs);
  void fadeOut(int fadeOutMs);

  /** 
   * Creates a MusicImpl object from the incoming description of the
   * music.
   * 
   * @param machine RLMachine context
   * @param track Description of the music
   * @return MusicImpl object
   * @throw Exception When the music described by track can't be found
   * or can't be played due to compile options.
   */
  static boost::shared_ptr<SDLMusic> CreateMusic(
    RLMachine& machine, const SoundSystem::DSTrack& track);

  /** 
   * Returns the currently playing SDLMusic object. Returns NULL if no
   * music is currently playing.
   */
  static boost::shared_ptr<SDLMusic> CurrnetlyPlaying()
  { return s_currentlyPlaying; }

  /// Whether music is currently playing.
  static bool IsCurrentlyPlaying() { return s_currentlyPlaying; }
};

// -----------------------------------------------------------------------

#endif