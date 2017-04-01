/**
 * Copyright (c) 2014-2016 by the respective copyright holders.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 */
package org.openhab.binding.gumyns;

public class Binding {
    public static final String ID = "gumyns";

    public final String binding;

    public final String address;

    public Binding(String binding, String address) {
        this.binding = binding;
        this.address = address;
    }
}
