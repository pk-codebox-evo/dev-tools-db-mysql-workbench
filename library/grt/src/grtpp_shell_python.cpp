/*
 * Copyright (c) 2009, 2017, Oracle and/or its affiliates. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301  USA
 */

#include "grtpp_shell_python.h"
#include "base/string_utilities.h"

using namespace grt;
using namespace base;

PythonShell::PythonShell() : _loader(0) {
}

void PythonShell::init() {
  _loader = dynamic_cast<PythonModuleLoader *>(grt::GRT::get()->get_module_loader(LanguagePython));
  if (!_loader)
    throw std::runtime_error("Python module loader not initialized");

  PythonContext *pycontext = _loader->get_python_context();

  pycontext->refresh();
}

void PythonShell::print_welcome() {
  print(strfmt("MySQL Generic Runtime Environment %s\n", GRT_VERSION));

  if (_disable_quit)
    print("\nType '?' for help.\n");
  else
    print("Type '?' for help. Type 'quit' to exit the shell.\n");
  print("Python Shell initialized. (Use Preferences -> General to set language)\n");
}

std::string PythonShell::get_prompt() {
  std::string cwd = _loader->get_python_context()->get_cwd();

  if (_current_line.empty())
    return cwd + ">>>";
  else
    return cwd + "...";
}

int PythonShell::execute_line(const std::string &linebuf) {
  return _loader->get_python_context()->run_buffer(linebuf, &_current_line);
}

int PythonShell::run_file(const std::string &file_name, bool interactive) {
  return _loader->get_python_context()->run_file(file_name, interactive);
}

std::vector<std::string> PythonShell::complete_line(const std::string &line, std::string &completed) {
  std::vector<std::string> tokens = get_tokens_for_prefix(line);
  if (tokens.size() == 1) {
    completed = tokens[0];
    tokens.clear();
  }
  return tokens;
}

static void add_matching_tokens_from_list(std::vector<std::string> &tokens, PyObject *list, const char *base,
                                          const char *prefix, const char *append = "") {
  for (Py_ssize_t i = 0; i < PyList_Size(list); i++) {
    const char *str = PyString_AsString(PyList_GetItem(list, i));
    if (g_str_has_prefix(str, prefix)) {
      if (base)
        tokens.push_back(strfmt("%s.%s%s", base, str, append));
      else
        tokens.push_back(strfmt("%s%s", str, append));
    }
  }
}

std::vector<std::string> PythonShell::get_tokens_for_prefix(const std::string &prefix) {
  std::vector<std::string> tokens;
  std::string::size_type dot = prefix.rfind('.');

  WillEnterPython lock;

  if (dot == std::string::npos) // SOMET
  {
    PyObject *module = PyImport_ImportModule("keyword");
    if (module) {
      PyObject *dict = PyModule_GetDict(module);
      if (dict) {
        PyObject *list = PyDict_GetItemString(dict, "kwlist");
        if (list)
          add_matching_tokens_from_list(tokens, list, NULL, prefix.c_str(), " ");
      }
    }

    module = PyImport_AddModule("__main__");
    if (module) {
      PyObject *dict = PyModule_GetDict(module);
      if (dict) {
        PyObject *list = PyDict_Keys(dict);
        add_matching_tokens_from_list(tokens, list, NULL, prefix.c_str());
        Py_DECREF(list);
      }

      PyObject *submod = PyDict_GetItemString(dict, "__builtins__");
      if (submod) {
        PyObject *list = PyObject_Dir(submod);
        if (list) {
          add_matching_tokens_from_list(tokens, list, NULL, prefix.c_str(), "(");
          Py_DECREF(list);
        }
      }
    }
    PyErr_Clear();
  } else // PREFIX.SOMET
  {
    std::string base = prefix.substr(0, dot);
    std::string pref = prefix.substr(dot + 1);

    PyObject *object = _loader->get_python_context()->eval_string(base);
    if (object) {
      // add results of dir()
      PyObject *list = PyObject_Dir(object);
      if (list) {
        add_matching_tokens_from_list(tokens, list, base.c_str(), pref.c_str());
        Py_DECREF(list);
      }
      Py_DECREF(object);
    }
    PyErr_Clear();
  }

  return tokens;
}

ValueRef PythonShell::get_global_var(const std::string &var_name) {
  ValueRef value;

  throw std::logic_error("not implemented");

  return value;
}

int PythonShell::set_global_var(const std::string &var_name, const ValueRef &value) {
  throw std::logic_error("not implemented");
  return 1;
}

extern void grt_shell_show_python_help(const char *command);

void PythonShell::show_help(const std::string &keyword) {
  grt_shell_show_python_help(keyword.c_str());
}
